
##  Ծրագրի Նկարագրություն

Այս նախագիծը իրականացված է `Spam Detection` խնդիր լուծելու նպատակով՝ օգտագործելով **TF-IDF** վեկտորիզացիա և **Լոգիստիկ ռեգրեսիա (Logistic Regression)**։  
Ծրագիրը կարող է տարբերակել «սփամ» և «սովորական» նամակները՝ տվյալների հիման վրա։

---

##  Ֆայլերի կառուցվածքը

```bash
 spam-detector/
├── include/
│   ├── TfidfVectorizer.h
│   ├── LogisticRegression.h
│   └── DataLoader.h
├── src/
│   ├── main.cpp
├── mail_data.csv
├── README.md
```

---

##  Օգտագործվող Ալգորիթմներ

### 1. **TF-IDF** (Term Frequency - Inverse Document Frequency)
- Թվային կերպ է ներկայացնում բառերը՝ հաշվի առնելով հաճախականությունը և եզակիությունը։

### 2. **Logistic Regression**
- Դասակարգիչ մոդել է, որը սովորում է `spam` և `ham` պիտակների հիման վրա։

---


###  **TF-IDF** (Term Frequency - Inverse Document Frequency)

**TF-IDF**-ը մեկական բառերի կարևորությունը որոշելու մեթոդ է՝ հաշվի առնելով այն, թե որքան հաճախ են դրանք հանդիպում տեքստում և որքան տարածված են դրանք մյուս փաստաթղթերում:



![image](https://github.com/user-attachments/assets/677a8059-7d17-4e5a-bb2a-2c46d27a7182)
![image](https://github.com/user-attachments/assets/232600f9-85c3-4ba1-b1a9-ac22042e5932)
![image](https://github.com/user-attachments/assets/7df17a23-2d67-4686-9698-689867e8d1d9)
![image](https://github.com/user-attachments/assets/df656e19-04f8-4b2f-ad53-3e367cea6467)
![image](https://github.com/user-attachments/assets/b86e0600-2119-47d6-9013-de8e407050a3)
![image](https://github.com/user-attachments/assets/e63e9f51-67ef-4817-8d8f-caa1d7eb5dcf)
![image](https://github.com/user-attachments/assets/9dacec3b-4fcc-4b91-8a39-c01e5c3e74f2)
![image](https://github.com/user-attachments/assets/c2e94c72-ad7b-4274-8f76-651eb1dcf100)
![image](https://github.com/user-attachments/assets/2eb655a6-9959-44a4-995c-eb6a44f11792)
![image](https://github.com/user-attachments/assets/99ae63fa-a22e-4771-94ee-e70fecd0cf05)
![image](https://github.com/user-attachments/assets/6ec85f24-c6a1-4100-9a39-73330c3d7ca1)




### **Կոդի Պատմություն**

1. **Տվյալների վերլուծություն (Preprocessing)**:  
   - Քաղվում են նամակների բառերը, նրանց հաճախականությունները հաշվում են, ապա հաշվարկվում են TF-IDF արժեքները։
  
2. **Մոդելի ուսուցում**:  
   - Մոդելն օգտագործում է լոգիստիկ ռեգրեսիա՝ ամեն մուտքային նամակի համար հիպոթեզի պիտակը հաշվարկելու համար։

3. **Կապակցված տվյալներ**:  
   - Քանի որ TF-IDF հաշվարկված է հենց բառերի հիանալի ներկայացման վրա, այն օգտագործվում է որպես մուտքային տվյալներ լոգիստիկ ռեգրեսիային։

---

###  Նկարագրություններ

#### 1. **TF-IDF- ի բառակապակցություններ**

```plaintext
      Words    --->   Frequency Calculation  --->   Term Frequency
        |                                 |
        v                                 v
    Document Count       --->    Inverse Document Frequency
        |                                 |
        v                                 v
      TF-IDF Calculation
```

#### 2. **Լոգիստիկ Ռեգրեսիայի Ուսուցում**

```plaintext
    Data Preprocessing
            |
            v
    Feature Vectorization  --->   Model Training  --->   Prediction
                                  (Logistic Regression)
            |
            v
        Evaluation
```

---

Այս նկարագրությունները ու մաթեմատիկական բացատրությունները պետք է ավելի լավ պատկերացնեն TF-IDF-ի և լոգիստիկ ռեգրեսիայի հաշվարկային մեթոդները։

##  C++ Կոդի Նկարագրություն

 Իմպլեմենտացված են **ձեռքով** հետևյալ դասերը.

- `TfidfVectorizer`: Վերլուծում է տեքստը, հաշվում է բառերի հաճախականությունը, հաշվարկում է TF-IDF արժեքները։
- `LogisticRegression`: Իրականացնում է train / predict մեթոդներ՝ լոգիստիկ ֆունկցիայով։

Օգտագործում է STL (`map`, `vector`, `string`, `cmath`)։  
Վերբեռնում է CSV ֆայլ, բաժանում train/test, ցուցադրում ճշգրտությունը։

```cpp
Accuracy: 0.9375
Prediction for new message: 1
```

---

##  Python Կոդի Նկարագրություն

 Իրականացվում է Google Colab-ում՝ օգտագործելով հետևյալ գրադարանները.

- `pandas`: CSV ֆայլերի համար
- `sklearn.feature_extraction.text.TfidfVectorizer`: Վեկտորիզացիայի համար
- `sklearn.linear_model.LogisticRegression`: Մոդելի ուսուցում
- `sklearn.model_selection.train_test_split`, `accuracy_score`

 Ավելի կոմպակտ է, սակայն կախված է արտաքին գրադարաններից։

```python
Accuracy: 0.9375
```

---

##  C++ և Python Համեմատություն

| Նկարագրություն        | C++                                     | Python                                        |
|----------------------|------------------------------------------|-----------------------------------------------|
| Տիպը                 | Ստորին մակարդակի                         | Բարձր մակարդակի                               |
| Գործառույթներ        | Ձեռքով իրագործված                        | Գրադարաններով                                 |
| Արտաքին գրադարաններ | Չկան                                     | Scikit-learn, pandas                          |
| Արագություն          | Ավելի բարձր                              | Ավելի դանդաղ                                   |
| Կոդի ծավալ           | Ավելի երկար                              | Ավելի համառոտ                                 |
| Ավելի հարմար         | Մշակման, ուսուցման և deployment-ի համար   | Փորձարկման և մոդելավորման համար                |

---

##  Մուտքային Տվյալների Ֆորմատ

### `mail_data.csv`
```csv
Category,Message
spam,You have won a free ticket!
ham,Hello, how are you today?
spam,Click here to claim your prize
```

---




###  Ծրագրի Workflow (Տվյալների նախապատրաստում և մոդելավորման հոսք)

```plaintext
[CSV File]
    |
    v
[Data Preprocessing (Cleaning & Splitting)]
    |
    v
[TF-IDF Vectorization]
    |
    v
[Logistic Regression Model]
    |
    v
[Prediction & Evaluation]
```





 Ներկայացվել է որպես կուրսային նախագիծ  
 Ստեղծվել է ՀԱՊՀ ՏՏ 219 Խմբի 3-րդ կուրսի ուսանողուհի էլիզա Մարտիրոսյանի կողմից


