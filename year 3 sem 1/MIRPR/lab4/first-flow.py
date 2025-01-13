# Import necessary libraries
import os   # jesus christ i have been losing sanity
os.environ["R_HOME"] = r"C:\\Program Files\\R\\R-4.4.1" 
os.environ["PATH"] = r"C:\\Program Files\\R\\R-4.4.1\\bin\\x64" + ";" + os.environ["R_HOME"] 
import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split, cross_val_score, StratifiedKFold
from sklearn.ensemble import RandomForestClassifier
from sklearn.svm import SVC
from sklearn.metrics import classification_report, confusion_matrix, accuracy_score
from sklearn.linear_model import LogisticRegression
from sklearn.tree import DecisionTreeClassifier
import seaborn as sns
import matplotlib.pyplot as plt
import warnings
from imblearn.over_sampling import SMOTE, ADASYN
from imblearn.under_sampling import RandomUnderSampler
from sklearn.model_selection import GridSearchCV
from sklearn.metrics import roc_auc_score, roc_curve
import rpy2.robjects as ro
from rpy2.robjects.packages import importr
from rpy2.robjects import pandas2ri
import time



# Suppress warnings for cleaner output
warnings.filterwarnings('ignore')

# Load the dataset
import pandas as pd

# Load the dataset
def load_data(file_path):
    """
    Load the dataset from a specified CSV or Excel file.
    """
    if file_path.endswith('.csv'):
        # Read CSV with appropriate settings
        data = pd.read_csv(file_path, header=0, dtype=str)  # Load all data as string
    else:
        # For Excel files, you might not need to set dtype
        data = pd.read_excel(file_path)

    # Ensure no categorical transformation by keeping all as string initially
    data = data.astype(str)

    return data

def run_mulset(data):
    print("Input DataFrame shape:", data.shape)
    print("Input DataFrame columns:", data.columns)
    print("Input DataFrame head:\n", data.head())

    # Import the mulset R library
    mulset = importr('mulset')

    # Convert the DataFrame to an R DataFrame
    r_data = pandas2ri.py2rpy(data)

    # Define parameters for mulset
    exclude = ['donor_id', 'outcome']
    include = ["samples", "samples_count"]
    max_intersections = 250

    # Run the mulset function to generate subsets
    mulset_results = mulset.mulset(r_data, exclude=exclude, include=include, maxIntersections=max_intersections)

    # Convert the R results back to a Pandas DataFrame
    result_list = []
    
    # Iterate through the results
    for idx in range(len(mulset_results)):
        result = mulset_results.rx2(idx + 1)  # Access the individual result in the list (R index starts at 1)

        # Debugging: print the names of the elements in the result
        print(f"Result {idx + 1} names:", result.names)
        
        # Extract the fields
        result_dict = {
            'features_hash': result.rx2('features_hash')[0],
            'feature_count': result.rx2('feature_count')[0],
            'features': ', '.join(result.rx2('features')),
            'samples': ', '.join(map(str, result.rx2('samples'))) if 'samples' in result.names else None,
            'samples_count': result.rx2('samples_count')[0] if 'samples_count' in result.names else None,
            'datapoints': result.rx2('datapoints')[0] if 'datapoints' in result.names else None
        }
        result_list.append(result_dict)

    subsets = pd.DataFrame(result_list)

    # Filter datasets based on the number of features and samples
    filtered_subsets = subsets[(subsets['feature_count'] >= 5) & (subsets['samples_count'] >= 15)]

    return filtered_subsets

# Test function to run mulset with test data
def test_mulset():
    test_data = pd.DataFrame({
        'outcome': ['low', 'high', 'low', 'high'],
        'age': [77, 61, 58, 90],
        'gender': ['male', 'female', 'female', 'male'],
        'Feature 7': [None, 7, 91, 20],
        'Feature 3': [0, None, 10, 0],
        'Feature 4': [28, 28, None, 5],
        'Feature 5': [5, 5, 18, None]
    })

    result = run_mulset(test_data)
    print(result)


# Preprocess the data
def preprocess_data(data):
    """
    Preprocess the dataset by handling missing values, converting categorical variables,
    and normalizing features if necessary.
    """
    # Check for missing values
    print("Missing values before preprocessing:\n", data.isnull().sum())

    original_columns = data.shape[1]
    
    # Use intersections to fill missing values or drop features
    # Here you would apply your strategy based on shared features identified by mulset
    data.dropna(axis=1, inplace=True)  # Example strategy: drop columns with missing values
   
    current_columns = data.shape[1]
    print(f"Dropped {original_columns - current_columns} columns with missing values.")


    if 'outcome' in data.columns:
        data['outcome'] = data['outcome'].map({'low': 0, 'high': 1})

    # Convert categorical columns to numeric if necessary
    data = pd.get_dummies(data, columns=['type'], drop_first=True)

    # Split features and target variable
    X = data.drop(columns=['Donor ID', 'outcome'])
    y = data['outcome']

    # Normalize the features (if needed)
    from sklearn.preprocessing import StandardScaler
    scaler = StandardScaler()
    X = scaler.fit_transform(X)

    # print our data, X and y
    print("Preprocessed DataFrame shape:", data.shape)
    print("Preprocessed DataFrame columns:", data.columns)
    print("Preprocessed DataFrame head:\n", data.tail())
    print("X shape:", X.shape)
    print("y shape:", y.shape)



    return X, y
# Train and validate the models using cross-validation
def train_validate_models(X, y):
    models = {
        "Random Forest": RandomForestClassifier(random_state=1337),
        "Support Vector Classifier": SVC(random_state=1337),
        "Logistic Regression": LogisticRegression(random_state=1337),
        "Decision Tree": DecisionTreeClassifier(random_state=1337)
    }

    cv_results = {}
    skf = StratifiedKFold(n_splits=5, shuffle=True, random_state=42)

    for model_name, model in models.items():
        print(f"\nValidating {model_name} with cross-validation...")
        cv_scores = cross_val_score(model, X, y, cv=skf)
        cv_results[model_name] = cv_scores
        print(f"{model_name} Cross-Validation Scores: {cv_scores}")
        print(f"{model_name} Average CV Score: {cv_scores.mean()}")

    return models, cv_results


def perform_grid_search(models, param_grids, X, y):
    best_models = {}
    best_params = {}
    for model_name, model in models.items():
        print(f"\nPerforming Grid Search for {model_name}...")
        grid_search = GridSearchCV(model, param_grids[model_name], cv=5, n_jobs=-1, verbose=1)
        grid_search.fit(X, y)
        best_models[model_name] = grid_search.best_estimator_
        best_params[model_name] = grid_search.best_params_
        print(f"Best parameters for {model_name}: {grid_search.best_params_}")
    return best_models, best_params

# Train the models on the entire training set
def train_models(models, X_train, y_train, best_params):
    trained_models = {}
    for model_name, model in models.items():
        print(f"\nTraining {model_name} with best parameters on the training set...")
        model.set_params(**best_params[model_name])
        model.fit(X_train, y_train)
        trained_models[model_name] = model
    return trained_models

# Evaluate models on the test set
def evaluate_models(models, X_test, y_test):
    for model_name, model in models.items():
        y_pred = model.predict(X_test)
        print(f"\nEvaluation for {model_name}:")
        print("Accuracy:", accuracy_score(y_test, y_pred))
        print("Classification Report:\n", classification_report(y_test, y_pred))
        print("Confusion Matrix:\n", confusion_matrix(y_test, y_pred))
        plt.figure(figsize=(10, 6))
        sns.heatmap(confusion_matrix(y_test, y_pred), annot=True, fmt='d', cmap='Blues', 
                    xticklabels=['Low', 'High'], yticklabels=['Low', 'High'])
        plt.title(f'Confusion Matrix for {model_name}')
        plt.xlabel('Predicted')
        plt.ylabel('True')
        plt.show()
        if len(set(y_test)) > 1:
            roc_auc = roc_auc_score(y_test, y_pred)
            print(f"ROC-AUC Score for {model_name}: {roc_auc}")
            fpr, tpr, _ = roc_curve(y_test, y_pred)
            plt.figure()
            plt.plot(fpr, tpr, color='darkorange', lw=2, label=f'ROC curve (area = {roc_auc:.2f})')
            plt.plot([0, 1], [0, 1], color='navy', lw=2, linestyle='--')
            plt.xlim([0.0, 1.0])
            plt.ylim([0.0, 1.05])
            plt.xlabel('False Positive Rate')
            plt.ylabel('True Positive Rate')
            plt.title(f'Receiver Operating Characteristic for {model_name}')
            plt.legend(loc='lower right')
            plt.show()
        else:
            print(f"ROC-AUC Score for {model_name}: Not applicable (only one class present)")


# Main function to execute the flow
def main(file_path):
    data = load_data(file_path)
    subsets = run_mulset(data)
    
    if not subsets.empty:
        X, y = preprocess_data(subsets)

        # Split the data into training and testing sets
        X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

        # Train and validate models using cross-validation
        models, cv_results = train_validate_models(X_train, y_train)

        # Train the models on the entire training set
        trained_models = train_models(models, X_train, y_train)

        # Evaluate the models on the test set
        evaluate_models(trained_models, X_test, y_test)
    else:
        print("No valid subsets generated from the mulset function.")

def mainWithoutMulset(file_path):
    data = load_data(file_path)
    X, y = preprocess_data(data)
    # print the shape of X and y
    
    X, y = SMOTE(random_state=1337).fit_resample(X, y)
    # here, undersample too
    rus = RandomUnderSampler(random_state=1337)
    X, y = rus.fit_resample(X, y)


    # use ADASYN instead of SMOTE
    # X, y = ADASYN(random_state=1337).fit_resample(X, y)

    print("Shape of X:", X.shape)
    print("Shape of y:", y.shape)
    if X.size > 0:
        # Split the data into training and testing sets
        X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.4, random_state=1337)

        # Train and validate models using cross-validation
        models, cv_results = train_validate_models(X_train, y_train)

        param_grids = {
            "Random Forest": {
                "n_estimators": [100, 200, 300],
                "max_depth": [None, 10, 20, 30],
                "min_samples_split": [2, 5, 10],
                "min_samples_leaf": [1, 2, 4],
                "max_features": [None, 'sqrt', 'log2']
            },
            "Support Vector Classifier": {
                "C": [0.1, 1, 10, 100],
                "kernel": ['linear', 'poly', 'rbf', 'sigmoid'],
                "gamma": ['scale', 'auto']
            },
            "Logistic Regression": {
                "C": [0.1, 1, 10, 100],
                "solver": ['newton-cg', 'lbfgs', 'liblinear', 'sag', 'saga'],
                "penalty": ['l2']
            },
            "Decision Tree": {
                "max_depth": [None, 10, 20, 30],
                "min_samples_split": [2, 5, 10],
                "min_samples_leaf": [1, 2, 4],
                "max_features": [None, 'sqrt', 'log2'],
                "criterion": ['gini', 'entropy']
            }
        }

        # ## Train the models on the entire training set
        # #trained_models = train_models(models, X_train, y_train)

        # trained_models = perform_grid_search(models, param_grids, X_train, y_train, X_test, y_test)

        # # Evaluate the models on the test set
        # evaluate_models(trained_models, X_test, y_test)
        models, cv_results = train_validate_models(X_train, y_train)
        best_models, best_params = perform_grid_search(models, param_grids, X_train, y_train)
        #trained_models = train_models(models, X_train, y_train, best_params)
        evaluate_models(best_models, X_test, y_test)
    else:
        print("No valid subsets generated from the mulset function.")


# Print statements and user prompts
# Shouldn't call other functions for now, just an UX
def flow():
    # Ask the user if they would like to run the analysis on a given dataset, for which they would have to provide the path, or retrain the models on a new dataset
    print("Welcome to the First Flow of Immune Predictors regarding Influenza.")
    print("Would you like to run the current models on a new dataset or retrain the models on a new dataset?")
    print("1. Run the analysis on a new dataset")
    print("2. Retrain the models on a new dataset")
    print("3. Exit")
    choice = input("Enter your choice (1/2/3): ")
    # switch case
    # Don't call main, just imitate the flow
    match choice:
        case "1":
            dataset_path = input("Enter the path to the new dataset: ")
            print("Loading the dataset...")
            # Wait a bit
            time.sleep(1)
            print("Dataset loaded successfully.")
            print("Running the analysis...")
            # Wait a bit
            time.sleep(1.5)
            print("Analysis completed.")
            print("Would you like to view the results in the terminal?")
            print("1. Yes")
            print("2. No, save to file")
            print("3. Exit")
            view_choice = input("Enter your choice (1/2/3): ")
            # switch case
            match view_choice:
                case "1":
                    print("Displaying the results...")
                    print("< huge table of results >")
                    # Save the results to a file?
                    print("Would you like to save the results to a file?")
                    print("1. Yes")
                    print("2. No")
                    save_choice = input("Enter your choice (1/2): ")
                    # switch case
                    match save_choice:
                        case "1":
                            # ask for file path, or add, to the dataset path, "_results.csv"
                            default_file_path = dataset_path.split(".")[0] + "_results.csv"
                            file_path = input("Enter the path to save the results: (Press Enter to save in the same directory as the dataset, to dataset_results.csv)")
                            if file_path == "":
                                file_path = default_file_path
                            print("Saving the results to path:", file_path)
                            time.sleep(1)
                        case "2":
                            flow()
                        case _:
                            print("Invalid choice. Please enter a valid choice (1/2).")    
                    flow()
                case "2":
                    # ask for file path, or add, to the dataset path, "_results.csv"
                    default_file_path = dataset_path.split(".")[0] + "_results.csv"
                    file_path = input("Enter the path to save the results: (Press Enter to save in the same directory as the dataset, to dataset_results.csv)")
                    if file_path == "":
                        file_path = default_file_path
                    print("Saving the results to path:", file_path)
                    flow()
                case "3":
                    print("Exiting the program...")
                    return
                case _:
                    print("Invalid choice. Please enter a valid choice (1/2/3).")
                    flow()

        case "2":
            dataset_path = input("Enter the path to the new dataset: ")
            print("Loading the dataset...")
            time.sleep(1.5)
            print("Dataset loaded successfully.")
            # Choose certain models, or all models
            print("Would you like to retrain all models or specific models?")
            print("1. Retrain all models")
            print("2. Retrain specific models")
            model_choice = input("Enter your choice (1/2): ")
            # switch case: if user chose 2, display all models and ask for the models to retrain, in a list
            match model_choice:
                case "2":
                    print("Choose the models to retrain:")
                    print("1. Random Forest")
                    print("2. Support Vector Classifier")
                    print("3. Both")
                    model_choice = input("Enter your choice (1/2/3): ")
                    # save the models to a path, or add, to the dataset path, "_models.pkl"
                    default_file_path = dataset_path.split(".")[0] + "_models.pkl"
                    file_path = input("Enter the path to save the models: (Press Enter to save in the same directory as the dataset, to dataset_models.pkl)")
                    if file_path == "":
                        file_path = default_file_path
                    print("Saving the models to path:", file_path)
                    time.sleep(1)
                    flow()
                case "1":
                    print("Retraining all models...")
                    time.sleep(1.5)
                    print("Models retrained successfully.")
                    default_file_path = dataset_path.split(".")[0] + "_models.pkl"
                    file_path = input("Enter the path to save the models: (Press Enter to save in the same directory as the dataset, to dataset_models.pkl)")
                    if file_path == "":
                        file_path = default_file_path
                    print("Saving the models to path:", file_path)
                    time.sleep(1)
                    flow()
            



        case "3":
            print("Exiting the program...")
            return
        case _:
            print("Invalid choice. Please enter a valid choice (1/2/3).")
            flow()
    
        
    


# Run the analysis
if __name__ == "__main__":
    pandas2ri.activate()
    # # Specify the path top your dataset
    # dataset_path = 'some data csv.csv'  # Change this to your dataset path
    # # main(dataset_path)

    # # just test mulset
    # data = load_data(dataset_path)
    # subsets = run_mulset(data)
    # print(subsets)
    # #test_mulset()
    # flow()

    # open "dataset 13.csv", drop last column (which is "training"/"testing"), separate into X and y, run the models
    dataset_path = "datasets\dataset 36.xlsx"
    dir = os.path.dirname(__file__)
    dataset_path = os.path.join(dir, dataset_path)

    print(f"Constructed dataset path: {dataset_path}")

    if not os.path.isfile(dataset_path):
        print(f"File not found: {dataset_path}")
    else:
        mainWithoutMulset(dataset_path)
