*The following is a report detailing working with a small dataset, also found in `lab3documentation-v1.md`. For the report regarding real data/bigger datasets, scroll past the performance plots.*
___
#### Overview

The aim of this project is to develop an intelligent algorithm to classify and predict immune responses to influenza vaccination, specifically identifying high and low responders based on various features from blood tests. We are utilizing several machine learning models, including Random Forest Classifier, Support Vector Classifier, Logistic Regression, and Decision Tree. The workflow involves data preprocessing, model training, hyperparameter optimization using Grid Search, and evaluation of model performance.

#### Data Preprocessing

**Purpose:**

-   To clean and prepare the data for model training and evaluation.
-   Handle missing values, convert categorical variables to numerical, and normalize features.

**Steps:**

1.  **Loading Data:** We load the dataset from an Excel or CSV file.
    
    ```
    def load_data(file_path):
        # Load the dataset from a specified CSV or Excel file.
	```
    
2.  **Handling Missing Values:** We drop columns with missing values to ensure clean data for model training.
    ```
    def preprocess_data(data):
        # Drop columns with missing values.
        data.dropna(axis=1, inplace=True)
    ```
    
3.  **Converting Categorical Variables:** Convert categorical columns to numerical using one-hot encoding.
    ```
    data = pd.get_dummies(data, columns=['type'], drop_first=True)
    ```
    
4.  **Feature and Target Separation:** Separate the features (X) from the target variable (y).
    
    ```
    X = data.drop(columns=['Donor ID', 'outcome'])
    y = data['outcome'].map({'low': 0, 'high': 1})
    ``` 
    
5.  **Normalization:** Normalize the feature values for better model performance.
    ```
    from sklearn.preprocessing import StandardScaler
    scaler = StandardScaler()
    X = scaler.fit_transform(X)
    ``` 
    

#### Model Training and Validation

**Purpose:**

-   To train various machine learning models and evaluate their performance using cross-validation.

**Steps:**

0. **Handling Class Imbalance with SMOTE and/or ADASYN**: 
    ```
	from imblearn.over_sampling import SMOTE
	from imblearn.over_sampling import ADASYN

	X, y = SMOTE(random_state=1337).fit_resample(X, y)
	# alternatively, use ADASYN instead of SMOTE
	# X, y = ADASYN(random_state=1337).fit_resample(X, y)
    ```

1.  **Splitting Data:** Split the data into training and testing sets.
    
    ```
    from sklearn.model_selection import train_test_split
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)
    ``` 
    
2.  **Defining Models:** Define the machine learning models to be used.
    ```
    models = {
        "Random Forest": RandomForestClassifier(random_state=42),
        "Support Vector Classifier": SVC(random_state=42),
        "Logistic Regression": LogisticRegression(random_state=42),
        "Decision Tree": DecisionTreeClassifier(random_state=42)
    }
    ```
    
3.  **Cross-Validation:** Perform cross-validation to assess the performance of each model.
    ```
    from sklearn.model_selection import cross_val_score
    cv_scores = cross_val_score(model, X, y, cv=5)
    ``` 
    

#### Hyperparameter Optimization

**Purpose:**

-   To optimize the hyperparameters of the models using Grid Search for better performance.

**Steps:**

1.  **Defining Hyperparameters Grid:** Define the grid of hyperparameters for each model.
    ```
    param_grid_rf = {
        'n_estimators': [50, 100, 200],
        'max_features': ['auto', 'sqrt', 'log2'],
        'max_depth': [None, 10, 20, 30]
    }
    ``` 
    
2.  **Grid Search:** Perform Grid Search to find the best hyperparameters.
    ```
    from sklearn.model_selection import GridSearchCV
    grid_search = GridSearchCV(estimator=model, param_grid=param_grid, cv=5, scoring='accuracy')
    grid_search.fit(X_train, y_train)
    ```
    

#### Model Evaluation

**Purpose:**

-   To evaluate the performance of the trained models on the test set using various metrics.

**Steps:**

1.  **Predictions:** Make predictions on the test set.
    ```
    y_pred = model.predict(X_test)
    ``` 
    
2.  **Metrics Calculation:** Calculate and display performance metrics like accuracy, classification report, confusion matrix, and ROC-AUC score.
    
    ```
    from sklearn.metrics import accuracy_score, classification_report, confusion_matrix, roc_auc_score
    accuracy = accuracy_score(y_test, y_pred)
    classification_report = classification_report(y_test, y_pred)
    confusion_matrix = confusion_matrix(y_test, y_pred)
    roc_auc = roc_auc_score(y_test, y_pred)
    ```





#### Models and Their Functionality
1.  **Random Forest Classifier:**
    
    -   **Description:**
        -   Random Forest is an ensemble learning method that constructs multiple decision trees during training. It uses the principle of bagging (Bootstrap Aggregating) where each tree is trained on a random subset of the data with replacement.
        -   Each tree in the forest is constructed independently using a random subset of features, which helps in reducing correlation among trees and improves the generalization ability of the model.
        -   The output class is determined by majority vote of the individual trees, making it robust to overfitting.
    -   **Advantages:**
        -   Handles large datasets with higher dimensionality.
        -   Effective at estimating missing data.
        -   Provides feature importance, which helps in understanding the influence of each feature on the prediction.
        -   Robust against overfitting due to averaging multiple decision trees.
    -   **Hyperparameters:**
        -   `n_estimators`: Number of trees in the forest. More trees generally improve the performance but at the cost of increased computational time.
        -   `max_depth`: Maximum depth of each tree. Controls the complexity of the model.
        -   `min_samples_split`: Minimum number of samples required to split an internal node. Helps to prevent overfitting.
        -   `min_samples_leaf`: Minimum number of samples required to be at a leaf node. Helps in smoothing the model.
        -   `max_features`: Number of features to consider when looking for the best split.
2.  **Support Vector Classifier (SVC):**
    
    -   **Description:**
        -   SVC is a supervised learning model that aims to find the optimal hyperplane that best separates the data into classes. It works well for both linear and non-linear classification by using kernel trick.
        -   The algorithm maximizes the margin between the data points of the two classes, which is the distance between the hyperplane and the closest points from either class.
        -   Kernel functions can be used to transform the input features into higher-dimensional space, making it possible to handle non-linear separations.
    -   **Advantages:**
        -   Effective in high-dimensional spaces and with a large number of features.
        -   Robust to overfitting, especially in high-dimensional space.
        -   Can handle non-linear relationships using kernel functions.
    -   **Hyperparameters:**
        -   `C`: Regularization parameter that controls the trade-off between achieving a low error on the training data and minimizing the norm of the coefficients.
        -   `kernel`: Specifies the kernel type to be used in the algorithm (e.g., linear, poly, rbf, sigmoid).
        -   `gamma`: Kernel coefficient for ‘rbf’, ‘poly’, and ‘sigmoid’. Defines how far the influence of a single training example reaches.
        -   `degree`: Degree of the polynomial kernel function (‘poly’). Ignored by other kernels.
3.  **Logistic Regression:**
    
    -   **Description:**
        -   Logistic Regression is a linear model for binary classification that models the probability of the outcome as a function of the input features. It uses the logistic function to squeeze the output of a linear equation between 0 and 1.
        -   The model estimates the parameters of the logistic function by maximizing the likelihood of the observed data.
        -   The decision boundary is a hyperplane that separates the two classes.
    -   **Advantages:**
        -   Simple and interpretable.
        -   Provides probability estimates, which can be useful in decision-making processes.
        -   Works well when the relationship between the independent and dependent variables is approximately linear.
        -   Can be regularized to prevent overfitting.
    -   **Hyperparameters:**
        -   `C`: Inverse of regularization strength. Smaller values specify stronger regularization.
        -   `solver`: Algorithm to use in the optimization problem (e.g., liblinear, newton-cg, lbfgs, sag, saga).
        -   `penalty`: Norm used in the penalization (e.g., l1, l2).
4.  **Decision Tree Classifier:**
    
    -   **Description:**
        -   Decision Trees split the data into subsets based on the value of input features. The splits are made in a way that increases the homogeneity of the resultant subsets.
        -   The tree is constructed by recursively partitioning the data until all leaf nodes are pure or contain fewer than the minimum number of samples required to split.
        -   Decision nodes represent decisions and leaf nodes represent outcomes.
    -   **Advantages:**
        -   Easy to interpret and visualize.
        -   Requires little data preprocessing (no need for normalization or dummy variables).
        -   Can capture non-linear relationships.
    -   **Hyperparameters:**
        -   `max_depth`: Maximum depth of the tree. Limits the number of splits and prevents overfitting.
        -   `min_samples_split`: Minimum number of samples required to split an internal node.
        -   `min_samples_leaf`: Minimum number of samples required to be at a leaf node.
        -   `max_features`: Number of features to consider when looking for the best split.
        -   `criterion`: Function to measure the quality of a split (e.g., gini, entropy).

#### Data Preparation

1.  **Loading the Dataset:**
    
    -   Data is loaded from a CSV or Excel file using pandas.
    -   All columns are initially loaded as strings to prevent automatic type conversion that may misrepresent the data.
2.  **Handling Missing Values:**
    
    -   Columns with missing values are dropped for simplicity. Imputation methods are used.
3.  **Feature Engineering:**
    
    -   Categorical features (e.g., gender) are converted into numerical representations using one-hot encoding.
    -   The outcome variable ('low' or 'high') is mapped to binary values (0 or 1).
4.  **Normalization:**
    
    -   Features are normalized using one of many Scalers (one is chosen) to ensure that each feature contributes equally to the model performance.
5.  **Balancing the Dataset:**
    
    -   Imbalanced datasets can lead to biased models. ***SMOTE*** (Synthetic Minority Over-sampling Technique) and/or ***ADASYN*** (Adaptive Synthetic Sampling) are used to generate synthetic samples for the minority class, ensuring a balanced dataset.

#### Model Training and Evaluation

1.  **Cross-Validation:**
    
    -   5-fold stratified cross-validation is used to validate each model. This ensures that the performance metrics are reliable and the model generalizes well to unseen data.
    -   Stratified cross-validation ensures that each fold has the same proportion of class labels as the original dataset, preventing bias in the training and validation process.
2.  **Hyperparameter Tuning:**
    
    -   Grid Search is used to identify the best hyperparameters for each model, optimizing for performance metrics like accuracy, precision, recall, and F1-score.
    -   Grid Search systematically works through multiple combinations of parameter tunes, cross-validating as it goes to determine which tune gives the best performance.
3.  **Training on the Full Training Set:**
    
    -   Once the best parameters are identified, models are trained on the entire training set to leverage all available data for training.
    -   This helps to improve the model's performance by utilizing more data.
4.  **Model Evaluation:**
    
    -   Models are evaluated on a separate test set to assess their performance. Key metrics include accuracy, precision, recall, F1-score, and ROC-AUC.
    -   Confusion matrices are generated to visualize the performance of each model in terms of true positives, true negatives, false positives, and false negatives.
5.  **Handling Class Imbalance in Evaluation:**
    
    -   Class weights are adjusted to handle imbalance in the training data.
    -   Evaluation metrics focus on both classes to ensure that the model performs well across the entire dataset.


![Confusion Matrix for Random Forest](../plots/ConfusionMatrixRandomForest.png)
![ROC for Random Forest](../plots/ROCRandomForest.png)
![Confusion Matrix for SVM](../plots/ConfusionMatrixSVC.png)
![ROC for SVM](../plots/ROCSVM.png)
![Confusion Matrix for Logistic Regression](../plots/ConfusionMatrixLogisticRegression.png)
![ROC for Logistic Regression](../plots/ROCLogisticRegression.png)
![Confusion Matrix for Decision Tree](../plots/ConfusionMatrixDecisionTree.png)
![ROC for Decision Tree](../plots/ROCDecisionTree.png)

___

The following is the report regarding working on real data and/or bigger datasets, including performance analysis.

*paths and filenames subject to change!*
*see `results/analysis` for .csv files*


#### Overview

The goal of this task is to train and save the best machine learning models for various datasets, each with different features and characteristics. We use a systematic approach to optimize, train, and save the models based on the best parameters identified in a prior optimization step. The trained models are then saved for future use.


#### Bigger Picture

1.  **Different Datasets with Different Features**:
    
    -   Each dataset represents different aspects of the problem domain and contains distinct features.
    -   The datasets are preprocessed to handle missing values, resampling for class imbalance, transformation, and scaling to ensure that the data is suitable for model training.
2.  **Optimization Process**:
    
    -   In the previous step, we optimized different models for each dataset using various preprocessing strategies and hyperparameters.
    -   The optimization process involved using cross-validation to identify the best combination of model, preprocessing strategies, and hyperparameters.
3.  **Saving Best Parameters**:
    
    -   The best model and its parameters for each dataset were saved in a CSV file (`SIMON_final_results_with_feature_importance.csv`).
    -   This CSV file contains detailed information about the best model for each dataset, including the preprocessing steps and the hyperparameters.

#### CSV File Structure

The results CSV file contains the following columns:

-   `Dataset`: The dataset number.
-   `Best Model`: The name of the best model.
-   `Combined Score`: The combined score used for ranking the models.
-   `AUROC`: The Area Under the Receiver Operating Characteristic curve score.
-   `Specificity`: The specificity score.
-   `Sensitivity`: The sensitivity score.
-   `F1 Score`: The F1 score.
-   `PR AUC`: The Precision-Recall AUC score.
-   `Best Parameters`: The best hyperparameters for the model.
-   `Transformation`: The transformation method used during preprocessing.
-   `Resample Strategy`: The resampling strategy used during preprocessing.
-   `Impute Strategy`: The imputation strategy used during preprocessing.
-   `Scaler`: The scaler used during preprocessing.
-   `Feature Importance`: The feature importance scores for the model (if available).

#### Models Used

The following machine learning models are considered:

-   **Random Forest**: An ensemble learning method using multiple decision trees for classification.
-   **Logistic Regression**: A statistical model that applies a logistic function to model binary dependent variables.
-   **Support Vector Classifier (SVC)**: A classifier that finds the hyperplane that best separates the data into different classes.
-   **Decision Tree**: A non-parametric supervised learning method used for classification by learning decision rules inferred from the data.

#### Preprocessing Steps

1.  **Imputation**:
    
    -   Missing values are imputed using either K-Nearest Neighbors (KNN) or Simple Mean Imputation.
    -   If the imputation strategy is 'KNN', `KNNImputer` is used.
    -   If the imputation strategy is 'mean', `SimpleImputer` with mean strategy is used.
2.  **Transformation**:
    
    -   Data is transformed to ensure normality and stabilize variance.
    -   If the transformation method is 'log', a logarithmic transformation is applied.
    -   If the transformation method is 'Yeo-Johnson', `PowerTransformer` with Yeo-Johnson method is used.
3.  **Resampling**:
    
    -   To handle class imbalance, resampling techniques like ADASYN and SMOTE are used.
    -   If the resampling strategy is 'ADASYN', `ADASYN` is used.
    -   If the resampling strategy is 'SMOTE', `SMOTE` is used.
4.  **Scaling**:
    
    -   Data is scaled to ensure that all features contribute equally to the model.
    -   If the scaler is 'standard', `StandardScaler` is used.
    -   If the scaler is 'robust', `RobustScaler` is used.
    -   If the scaler is 'minmax', `MinMaxScaler` is used.

#### Feature Extraction

-   For models like Random Forest and Decision Tree, feature importances are extracted using the `feature_importances_` attribute.
-   For linear models like Logistic Regression, feature importances are extracted using the `coef_` attribute.
-   Feature importances are used to identify the top features contributing to the model's predictions.
- These are eventually saved in `aggregated_SOSA_results` alongside the other information for each dataset & model pair.

#### Algorithm

1.  **Load the Results File**: The CSV file containing the best models and their parameters is loaded into a DataFrame (`results_df`).
    
2.  **Iterate Over Each Dataset**:
    
    -   Extract the dataset number, best model name, best parameters, transformation, resampling strategy, imputation strategy, and scaler from the DataFrame.
3.  **Load the Training Data**:
    
    -   The training data for the current dataset is loaded from the specified path.
    -   The data is split into features (`X_train`) and the target variable (`y_train`).
4.  **Data Preprocessing**:
    
    -   The data is preprocessed according to the strategies specified in the results file.
5.  **Model Training**:
    
    -   The model is initialized with the best parameters specified in the results file.
    -   The model is trained using the preprocessed training data.
6.  **Saving the Trained Model**:
    
    -   The trained model is saved to a `.joblib` file in the specified model save path.

___

The following is a summary of the performances of the trained models; this represents the findings from the aggregated SOSA results across various datasets. Each dataset was evaluated using different models, and the best performing model along with its scores and parameters is highlighted.
*(can be scrolled horizontally)*

| **Dataset** | **Best Model**          | **Combined Score** | **AUROC** | **Specificity** | **Sensitivity** | **F1 Score** | **PR AUC** | **Best Parameters**                                                       | **Transformation** | **Resample Strategy** | **Impute Strategy** | **Scaler** | **Feature Importance** |
|-------------|-------------------------|--------------------|-----------|-----------------|-----------------|--------------|------------|---------------------------------------------------------------------------|---------------------|-----------------------|---------------------|------------|------------------------|
| 1           | Support Vector Classifier | 0.687              | 0.648     | 0.385           | 0.857           | 0.571        | 0.479      | `{'kernel': 'poly', 'gamma': 'scale', 'C': 10.0}`                          | log                 | SMOTE                 | KNN                 | robust     | No                     |
| 3           | Support Vector Classifier | 0.722              | 0.813     | 0.692           | 0.714           | 0.625        | 0.801      | `{'kernel': 'rbf', 'gamma': 'scale', 'C': 0.1}`                             | log                 | SMOTE                 | KNN                 | robust     | No                     |
| 4           | Decision Tree            | 0.327              | 0.417     | 0.750           | 0.333           | 0.333        | 0.311      | `{'min_samples_split': 10, 'min_samples_leaf': 4, 'max_features': 'sqrt', 'max_depth': None}` | Yeo-Johnson         | SMOTE                 | KNN                 | robust     | Yes                    |
| 5           | Decision Tree            | 0.476              | 0.729     | 0.833           | 0.500           | 0.500        | 0.420      | `{'min_samples_split': 5, 'min_samples_leaf': 2, 'max_features': None, 'max_depth': None}` | log                 | ADASYN                | KNN                 | robust     | Yes                    |
| 7           | Support Vector Classifier | 0.775              | 0.806     | 0.783           | 0.818           | 0.720        | 0.738      | `{'kernel': 'poly', 'gamma': 'scale', 'C': 10.0}`                          | Yeo-Johnson         | ADASYN                | KNN                 | robust     | No                     |
| 8           | Support Vector Classifier | 0.616              | 0.439     | 0.286           | 0.786           | 0.550        | 0.378      | `{'kernel': 'poly', 'gamma': 'auto', 'C': 10.0}`                           | Yeo-Johnson         | SMOTE                 | KNN                 | robust     | No                     |
| 9           | Support Vector Classifier | 0.707              | 0.560     | 0.000           | 0.857           | 0.533        | 0.572      | `{'kernel': 'poly', 'gamma': 'scale', 'C': 0.01}`                          | log                 | SMOTE                 | KNN                 | robust     | No                     |
| 10          | Random Forest            | 0.312              | 0.472     | 0.833           | 0.333           | 0.333        | 0.262      | `{'n_estimators': 400, 'min_samples_split': 2, 'min_samples_leaf': 2, 'max_features': 'sqrt', 'max_depth': 10}` | Yeo-Johnson         | SMOTE                 | KNN                 | robust     | Yes                    |
| 12          | Random Forest            | 0.680              | 0.778     | 0.667           | 0.667           | 0.571        | 0.774      | `{'n_estimators': 200, 'min_samples_split': 2, 'min_samples_leaf': 1, 'max_features': 'sqrt', 'max_depth': 20}` | log                 | ADASYN                | KNN                 | robust     | Yes                    |
| 13          | Random Forest            | 0.756              | 0.909     | 0.909           | 0.750           | 0.750        | 0.771      | `{'n_estimators': 300, 'min_samples_split': 2, 'min_samples_leaf': 1, 'max_features': None, 'max_depth': None}` | log                 | ADASYN                | KNN                 | robust     | Yes                    |
| 15          | Support Vector Classifier | 0.839              | 0.861     | 0.583           | 1.000           | 0.706        | 0.661      | `{'kernel': 'poly', 'gamma': 'auto', 'C': 10.0}`                           | log                 | SMOTE                 | KNN                 | robust     | No                     |
| 32          | Support Vector Classifier | 0.723              | 0.585     | 0.000           | 0.909           | 0.541        | 0.536      | `{'kernel': 'poly', 'gamma': 'scale', 'C': 0.01}`                          | log                 | SMOTE                 | KNN                 | robust     | No                     |
| 33          | Support Vector Classifier | 0.839              | 0.688     | 0.250           | 1.000           | 0.727        | 0.646      | `{'kernel': 'poly', 'gamma': 'scale', 'C': 10.0}`                          | Yeo-Johnson         | ADASYN                | KNN                 | robust     | No                     |
| 34          | Support Vector Classifier | 0.793              | 0.750     | 0.750           | 1.000           | 0.750        | 0.478      | `{'kernel': 'linear', 'gamma': 'auto', 'C': 1000.0}`                       | log                 | ADASYN                | KNN                 | standard   | Yes                    |
___
The following is a table of the top features found in each dataset - note that for some datasets, the top features are not available *(yet)*
| **Dataset** | **Top Features**                                                                                                      | **Top Importance**                                                                                  |
|-------------|------------------------------------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------------|
| 1           |                                                                                                                        |                                                                                                     |
| 3           |                                                                                                                        |                                                                                                     |
| 4           | `['IFNa_CD8_pos_pSTAT5', 'Unstim_B_cell_pSTAT1', 'IFNg_CD8_pos_pSTAT5', 'IFNa_Mono_pSTAT1', 'Unstim_CD8_pos_pSTAT5']`  | `[0.58669173 0.24921659 0.12370266 0.02065217 0.01973684]`                                          |
| 5           | `['CD161_pos_CD45RA_pos_Tregs', 'IgD_pos_CD27_pos_B_cells', 'CD85j_pos_CD8_pos_T_cells', 'HLADR_pos_CD38_neg_CD8_pos_T_cells', 'memory_B_cells']` | `[0.39601244 0.276372   0.23031    0.07106132 0.02624424]`                                          |
| 7           |                                                                                                                        |                                                                                                     |
| 8           |                                                                                                                        |                                                                                                     |
| 9           |                                                                                                                        |                                                                                                     |
| 10          | `['effector_CD8_pos_T_cells', 'HLADR_pos_NK_cells', 'CD161_pos_NK_cells', 'transitional_B_cells', 'effector_CD4_pos_T_cells']` | `[0.10149392 0.07536011 0.05768766 0.05325003 0.04617378]`                                          |
| 12          | `['L50_IL1RA', 'L50_VEGF', 'Unstim_B_cell_pSTAT1', 'Unstim_Mono_pSTAT5', 'L50_GMCSF']`                                | `[0.04469073 0.03139255 0.03006337 0.02988671 0.02796795]`                                          |
| 13          | `['CD161_pos_CD45RA_pos_Tregs', 'Th2_non_neg_TFH_CD8_pos_T_cells', 'CD27_pos_CD8_pos_T_cells', 'Th17_TFH_CD8_pos_T_cells', 'CD57_pos_CD4_pos_T_cells']` | `[0.3086581  0.06576466 0.06053811 0.05611575 0.03482373]`                                          |
| 15          |                                                                                                                        |                                                                                                     |
| 32          |                                                                                                                        |                                                                                                     |
| 33          |                                                                                                                        |                                                                                                     |
| 34          | `['memory_B_cells', 'monocytes', 'effector_CD8_pos_T_cells', 'L50_HGF', 'L50_MIP1B']`                                | `[0.20909122 0.20829598 0.19098168 0.18692426 0.16771616]`                                          |
| 35          | `['CD161_pos_CD45RA_neg_Tregs', 'Tregs', 'L50_MCP3', 'naive_CD8_pos_T_cells', 'NKT_cells']`                           | `[0.23424077 0.17745218 0.14146773 0.13333333 0.099702]`                                           |
| 36          | `['monocytes', 'L50_TRAIL', 'TNFA', 'effector_CD8_pos_T_cells', 'plasmablasts']`                                      | `[0.1949758  0.17269822 0.16808635 0.16219674 0.16179674]`                                          |
| 41          |                                                                                                                        |                                                                                                     |
| 168         | `['IL_neg_21_CD8_pos_CD45RA_pos_pSTAT5', 'Unstim_CD4_pos_CD45RA_pos_pSTAT5', 'IFNa_Mono_pSTAT5', 'IgD_neg_CD27_neg_B_cells', 'IL_neg_10_CD4_pos_CD45RA_neg_pSTAT5']` | `[0.65024631 0.32662444 0.02312925 0.         0.        ]`                                          |
| 169         | `['IL_neg_10_CD4_pos_pSTAT1', 'IL_neg_6_CD8_pos_pSTAT1', 'L50_MCP1', 'IgD_pos_CD27_neg_B_cells', 'IFNg_B_cell_pSTAT3']` | `[0.43410293 0.20182117 0.17493386 0.12333516 0.03306878]`                                          |
| 171         |                                                                                                                        |                                                                                                     |
| 202         | `['IL_neg_6_CD4_pos_pSTAT5', 'IL_neg_10_CD4_pos_CD45RA_neg_pSTAT5', 'IL_neg_10_CD4_pos_CD45RA_neg_pSTAT3', 'IL_neg_10_CD4_pos_CD45RA_pos_pSTAT1', 'IL_neg_10_CD4_pos_CD45RA_pos_pSTAT3']` | `[0.72727273 0.27272727 0.         0.         0.        ]`                                          |

___
What follows is to re-train models on the datasets which yielded models with unaccessible features. Afterwards, all the features will be collected and we will begin data extraction from the big FluPRINT dataset, `fluprint_export`.
