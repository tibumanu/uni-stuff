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