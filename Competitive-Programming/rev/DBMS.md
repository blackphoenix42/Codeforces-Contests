## 🔷 1. Introduction to DBMS

---

### 🔹 What is DBMS? Advantages over File Systems

#### ✅ Definition:

A **Database Management System (DBMS)** is a software that interacts with the user, applications, and the database itself to capture and analyze data. It allows for **efficient data storage, retrieval, and management** while providing **data integrity, concurrency control, and security**.

#### 🆚 File System vs DBMS:

| Feature           | File System              | DBMS                                 |
| ----------------- | ------------------------ | ------------------------------------ |
| Data Redundancy   | High                     | Low                                  |
| Data Consistency  | Hard to maintain         | Enforced through constraints         |
| Security          | Basic (OS-level)         | Fine-grained access control          |
| Querying          | Manual (custom programs) | Declarative (SQL)                    |
| Transactions      | Not supported            | ACID properties                      |
| Backup & Recovery | Manual                   | Automated                            |
| Concurrent Access | Risk of corruption       | Controlled via concurrency protocols |

#### 🌐 Real-World Scenario:

**Scenario:** A library system using flat files vs DBMS.

- File system: Each book has a separate file → redundancy of author info → hard to update across all.
- DBMS: Author and book tables separated → only 1 update needed → consistency and maintainability.

---

### 🔹 Characteristics of DBMS

#### ✅ Key Characteristics:

1. **Self-describing nature** (metadata stored in the catalog)
2. **Data abstraction** (via 3-tier architecture)
3. **Program-data independence**
4. **Data Integrity and Security**
5. **Multi-user access and concurrency control**
6. **Transaction support (ACID)**
7. **Backup and Recovery mechanisms**

#### 🔍 Diagram – DBMS Architecture:

```
+--------------------------+
|     External Level       |  <- View 1, View 2, ...
+--------------------------+
|    Conceptual Level      |  <- Logical structure of the DB
+--------------------------+
|     Internal Level       |  <- Physical storage
+--------------------------+
```

---

### 🔹 Users of DBMS

#### ✅ Types of Users:

| User Type                        | Description                                             |
| -------------------------------- | ------------------------------------------------------- |
| **Database Administrator (DBA)** | Responsible for schema definition, security, backup     |
| **Database Designers**           | Define the structure of database (schemas, constraints) |
| **Application Programmers**      | Develop app logic using SQL or APIs                     |
| **End Users**                    | Interact with system via GUI/queries                    |

#### 🌐 Real-World Scenario:

**Example:** In an online banking system:

- DBA controls access permissions and backups.
- Developers write code for account transfers.
- End-users check balances or transfer money.

---

### 🔹 Instances vs Schemas

#### ✅ Definitions:

- **Schema**: Logical structure of the database. Defined once during design. (e.g., Tables, fields, types).
- **Instance**: Snapshot of data in the database at a particular moment.

#### 📥 Example:

- Schema: Table `Employee(EID, Name, Age)`
- Instance:
  ```
  +-----+--------+-----+
  | EID | Name   | Age |
  +-----+--------+-----+
  | 101 | Alice  | 28  |
  | 102 | Bob    | 34  |
  +-----+--------+-----+
  ```

#### 🔍 Diagram – Schema vs Instance:

```
           SCHEMA
           ------
         Employee
        /    |    \
      EID  Name   Age

           INSTANCE
           --------
  EID   Name    Age
  101   Alice    28
  102   Bob      34
```

#### 🌐 Real-World Q&A:

**Q:** Why is schema rarely changed in production systems?  
**A:** Because changing schema affects all applications using the DB. Costly and error-prone.  
Instead, new fields are added or schema versioning is used.

---

### 🔹 Data Abstraction (Physical, Logical, View Levels)

#### ✅ Definition:

**Data Abstraction** is the process of hiding implementation details of data storage and showing only essential features to users. It allows the user to interact with the database without worrying about **how data is stored or organized internally**.

#### ✅ Levels of Abstraction:

1. **Physical Level (Internal)** –  
   How the data is physically stored on disk (files, blocks, indexes, B+ trees, etc.)

2. **Logical Level (Conceptual)** –  
   What data is stored and what the relationships are (e.g., tables, attributes)

3. **View Level (External)** –  
   How users view data (subsets, renaming, hiding columns)

#### 🔍 Diagram – Data Abstraction:

```
        +-------------------+
        |  View Level       | ← Multiple user views
        +-------------------+
        | Logical Level     | ← Schema, tables, relations
        +-------------------+
        | Physical Level    | ← Files, indexes, blocks
        +-------------------+
```

#### 🌐 Real-World Analogy:

- **View Level** → Bank customer sees their account balance
- **Logical Level** → System stores transactions, accounts, customers
- **Physical Level** → Disk has B+ Trees and tables with pointers

---

### 🔹 Data Independence (Logical vs Physical)

#### ✅ Definition:

**Data Independence** refers to the ability to change the schema at one level of the database system without having to alter the schema at the next higher level.

#### ✅ Types of Data Independence:

1. **Physical Data Independence** –  
   Changing the **physical storage** (e.g., indexes, file structures) without affecting the **logical schema**.

2. **Logical Data Independence** –  
   Changing the **logical schema** (e.g., table definitions, attributes) without affecting the **view level** or user queries.

#### 📥 Example:

- **Physical**: Moving from hash-based file to B+ Tree index without changing table definitions.
- **Logical**: Adding a column `email` to `Customer` table – views like `SELECT Name` shouldn't break.

#### 🌐 Real-World Q&A:

**Q:** Why is Logical Data Independence harder to achieve than Physical?  
**A:** Because user applications depend directly on logical schema (e.g., column names, joins).

---

### 🔹 3-Tier Architecture (Internal, Conceptual, External)

#### ✅ Definition:

This is an architectural framework for DBMS that separates the database system into three layers to support abstraction and independence.

#### ✅ Layers:

1. **Internal Level (Storage / Physical)** –  
   Actual physical storage of data, indexing, data compression

2. **Conceptual Level (Logical Schema)** –  
   Structure of the whole database: entities, data types, relationships

3. **External Level (User View)** –  
   Individual views for different users. Could be restricted or renamed.

#### 🔍 Diagram – 3-Tier Architecture:

```
        +------------------+
        |  External Level  |
        | (User Views)     |
        +------------------+
                 |
        +------------------+
        | Conceptual Level |
        | (Logical Schema) |
        +------------------+
                 |
        +------------------+
        |  Internal Level  |
        | (Physical Storage)|
        +------------------+
```

#### 🌐 Real-World Scenario:

- **External View**: Customer sees `Name, Balance`
- **Conceptual View**: Full table with `AccountNo, Name, Balance, Email`
- **Internal View**: Disk has pages with clustered indexing

---

### 🔹 Database Languages (DDL, DML, DCL, TCL)

#### ✅ Categories of DBMS Languages:

| Language Type | Full Form                    | Purpose                               | Example Commands                       |
| ------------- | ---------------------------- | ------------------------------------- | -------------------------------------- |
| **DDL**       | Data Definition Language     | Define structure of database objects  | `CREATE`, `ALTER`, `DROP`, `TRUNCATE`  |
| **DML**       | Data Manipulation Language   | Insert, update, delete data           | `INSERT`, `UPDATE`, `DELETE`, `SELECT` |
| **DCL**       | Data Control Language        | Manage permissions and access control | `GRANT`, `REVOKE`                      |
| **TCL**       | Transaction Control Language | Handle transactions                   | `COMMIT`, `ROLLBACK`, `SAVEPOINT`      |

#### 💻 Sample Code:

```sql
-- DDL
CREATE TABLE Students (ID INT, Name VARCHAR(100));

-- DML
INSERT INTO Students VALUES (1, 'Ayush');

-- DCL
GRANT SELECT ON Students TO public;

-- TCL
COMMIT;
```

#### 📤 Output Sample:

After above insert and commit:

```sql
SELECT * FROM Students;
-- Output:
-- | ID | Name  |
-- |----|-------|
-- | 1  | Ayush |
```

#### 🌐 Real-World Q&A:

**Q:** Why separate TCL from DML?  
**A:** Because transactions can include multiple DML operations; TCL ensures **atomicity and durability**.

---

### 🔹 DBMS vs RDBMS vs NoSQL

#### ✅ Definitions:

- **DBMS (Database Management System)**: A general-purpose software for storing and managing data in a structured format. It supports flat-file or semi-structured formats but may not enforce relational integrity.
- **RDBMS (Relational Database Management System)**: A type of DBMS that follows the **relational model** introduced by E.F. Codd. It stores data in **tables** with enforced **keys**, **constraints**, and **relationships**.

- **NoSQL (Not Only SQL)**: A category of DBMS that stores data in non-relational formats like **key-value pairs**, **documents**, **graphs**, or **columns**. Optimized for **horizontal scaling**, **schema flexibility**, and **unstructured/semi-structured data**.

---

#### ✅ Key Differences Table:

| Feature                | DBMS                      | RDBMS                         | NoSQL                             |
| ---------------------- | ------------------------- | ----------------------------- | --------------------------------- |
| Data Model             | Hierarchical / File-based | Tabular (relations)           | Document, Key-Value, Graph, etc.  |
| Schema Enforcement     | Loose                     | Strict schema                 | Flexible schema                   |
| Support for Keys       | Not mandatory             | Enforces primary/foreign keys | Often does not enforce            |
| Data Integrity         | Limited                   | Strong (constraints)          | Weak                              |
| Query Language         | Proprietary or basic      | Structured Query Language     | Varies (MongoQL, CQL, etc.)       |
| ACID Compliance        | Partial                   | Strongly ACID compliant       | Often BASE (Eventual consistency) |
| Horizontal Scalability | Limited                   | Moderate                      | High                              |
| Use Case               | Local, single-user apps   | Enterprise, transactional     | Big Data, Real-time analytics     |

---

#### 🔍 Diagram – Classification:

```
          +-----------------+
          |     DBMS        |
          +-----------------+
               /       \
      +--------+       +----------+
      | RDBMS  |       |  NoSQL   |
      +--------+       +----------+
       (SQL)          (Non-SQL)
     e.g., MySQL     e.g., MongoDB
```

---

#### 🌐 Real-World Use Cases:

- **DBMS**: Used in legacy applications like Microsoft Access for small desktop-based systems.
- **RDBMS**: Used in banking, e-commerce, ERP systems.
- **NoSQL**: Used in IoT, real-time analytics, social media platforms (e.g., Twitter, Instagram).

---

#### 🌐 Real-World Q&A:

**Q:** Can NoSQL databases support SQL?  
**A:** Some do (e.g., Cassandra’s CQL), but generally NoSQL systems use domain-specific query languages.

**Q:** Why prefer RDBMS for banking?  
**A:** Because banking requires **strong consistency**, **ACID transactions**, and **structured data**.

---

### 🔹 Popular DBMS Software

#### ✅ Relational Databases (RDBMS):

| Name           | Type  | Key Features                          | Use Case                        |
| -------------- | ----- | ------------------------------------- | ------------------------------- |
| **MySQL**      | RDBMS | Open-source, fast, widely used        | Web apps (LAMP stack)           |
| **PostgreSQL** | RDBMS | Open-source, supports JSON, full ACID | Complex queries, GIS, analytics |
| **Oracle**     | RDBMS | Enterprise-grade, PL/SQL, scalability | Finance, ERP, telecom           |
| **SQL Server** | RDBMS | Developed by Microsoft, T-SQL         | Windows-based applications      |
| **SQLite**     | RDBMS | Embedded, serverless, single-file DB  | Mobile apps, lightweight apps   |

#### ✅ NoSQL Databases:

| Name                | Type           | Key Features                             | Use Case                         |
| ------------------- | -------------- | ---------------------------------------- | -------------------------------- |
| **MongoDB**         | Document Store | Stores JSON-like BSON docs               | CMS, analytics, IoT              |
| **Cassandra**       | Column Store   | Horizontal scaling, eventual consistency | Time-series, Big Data            |
| **Redis**           | Key-Value      | In-memory, super fast                    | Caching, leaderboard systems     |
| **Neo4j**           | Graph DB       | Nodes + edges, relationship modeling     | Social networks, fraud detection |
| **Amazon DynamoDB** | Key-Value      | Fully managed NoSQL, highly scalable     | Cloud-based, real-time apps      |

---

#### 💻 Sample Code:

```sql
-- MySQL: Basic relational query
SELECT Name FROM Customers WHERE Balance > 10000;

-- MongoDB: NoSQL query (document-based)
db.customers.find({ balance: { $gt: 10000 } }, { name: 1 });
```

#### 📤 Output Sample (Both):

```text
Name
-----
"Ravi"
"Anjali"
```

---

#### 🌐 Real-World Q&A:

**Q:** Which DB to choose for mobile app with offline storage?  
**A:** **SQLite** – serverless, lightweight, no setup required.

**Q:** Why is PostgreSQL often preferred in startups?  
**A:** Open-source, supports advanced features (window functions, JSON), ACID-compliant, and free.

**Q:** Can NoSQL databases be used in financial systems?  
**A:** Rarely. Due to weaker ACID support, they’re less suited for high consistency use-cases.

---

## 🔷 2. Data Models

---

### 🔹 Relational Model (Most Important)

#### ✅ Definition:

The **Relational Data Model** represents data as **relations (tables)**, where each table has rows (**tuples**) and columns (**attributes**). It is based on **set theory and first-order predicate logic**.

#### ✅ Key Terms:

- **Relation**: A table
- **Tuple**: A row
- **Attribute**: A column
- **Schema**: Structure of a table (e.g., `Student(RollNo, Name, Age)`)

#### 📥 Example:

```text
Table: Student

+--------+---------+-----+
| RollNo | Name    | Age |
+--------+---------+-----+
| 101    | Ayush   | 21  |
| 102    | Priya   | 22  |
+--------+---------+-----+
```

#### 🔍 Diagram – Relational View:

```
      Student
   +--------+--------+-----+
   | RollNo | Name   | Age |
   +--------+--------+-----+
   | 101    | Ayush  | 21  |
   | 102    | Priya  | 22  |
   +--------+--------+-----+
```

#### 🌐 Real-World Q&A:

**Q:** Why is the relational model most widely used?  
**A:** Simplicity, flexibility, and strong theoretical foundation. It maps naturally to SQL and tabular data.

**Q:** Can the relational model represent complex relationships?  
**A:** Yes, via **foreign keys** and **joins** between tables.

---

### 🔹 Hierarchical Model

#### ✅ Definition:

A **tree-based model** where data is organized in a **parent-child hierarchy**. Each child has exactly one parent, forming a **one-to-many** relationship.

#### 🔍 Diagram:

```
           Department
               |
       +-------+-------+
       |               |
   Employee         Intern
```

#### 📥 Example:

```text
Department → Employee → Salary
```

#### ✅ Key Features:

- Fast access if hierarchy is fixed
- Efficient for **1:N relationships**
- Represented using **pointers or tree structures**

#### 🌐 Real-World Q&A:

**Q:** Where is the hierarchical model used?  
**A:** Legacy systems like **IBM's IMS**, **file systems (NTFS)**.

**Q:** Limitation?  
**A:** Poor flexibility for complex or many-to-many relationships.

---

### 🔹 Network Model

#### ✅ Definition:

A **graph-based model** where entities are organized as **records** connected through **set-based relationships** (many-to-many allowed). Supports multiple parent-child links (unlike hierarchical).

#### 🔍 Diagram:

```
   +--------+     +--------+
   | Dept A | <-->| Emp 01 |
   +--------+     +--------+
       ^              ^
       |              |
   +--------+     +--------+
   | Dept B |     | Emp 02 |
   +--------+     +--------+
```

#### 📥 Representation:

- Uses **pointers** to traverse between connected records
- Designed using **schema diagrams** with nodes and arrows

#### ✅ Use Cases:

- Flexible representation of **complex relationships**
- Suitable for **manufacturing**, **telecom networks**

#### 🌐 Real-World Q&A:

**Q:** What DB uses Network Model?  
**A:** **CODASYL** databases in early mainframes.

**Q:** Disadvantage?  
**A:** Complexity of maintaining **pointer navigation logic**.

---

### 🔹 Object-Oriented Data Model (OODM)

#### ✅ Definition:

An advanced model that combines **object-oriented programming** principles with database features. Data is represented as **objects**, similar to classes in OOP languages.

#### ✅ Features:

- Supports **encapsulation**, **inheritance**, **polymorphism**
- Attributes + Methods
- Relationships modeled via references

#### 📥 Example:

```cpp
class Student {
    int rollNo;
    string name;
    int age;
    void enroll();
}
```

In OODM, this `Student` object is stored directly with its methods in the database.

#### 🔍 Diagram:

```
[Student]
 | rollNo: int
 | name: string
 | age: int
 | enroll(): void
```

#### ✅ Benefits:

- Seamless mapping from OOP code to DB
- Complex objects supported natively
- Extensible

#### 🌐 Real-World Q&A:

**Q:** Where is OODM used?  
**A:** **CAD/CAM**, **multimedia systems**, **real-time simulations**

**Q:** Example DBMS?  
**A:** **db4o**, **ObjectDB**, and object-relational features in **PostgreSQL**

---

### 🔹 Summary: Comparison of Data Models

| Feature        | Relational Model | Hierarchical Model   | Network Model | Object-Oriented Model  |
| -------------- | ---------------- | -------------------- | ------------- | ---------------------- |
| Structure      | Tables           | Tree                 | Graph         | Classes/Objects        |
| Relationships  | 1:1, 1:N, M:N    | 1:N only             | 1:N, M:N      | Complex + Inheritance  |
| Flexibility    | High             | Low                  | Medium        | High                   |
| Usage          | Modern systems   | Legacy, file systems | Telecom, old  | CAD, real-time systems |
| Query Language | SQL              | Navigational         | Navigational  | Object Query Language  |

---

### 🔹 Entity-Relationship Model (ER Model)

#### ✅ Definition:

The **ER Model** is a high-level conceptual data model used to **design the structure of a database**. It describes data as **entities**, **attributes**, and **relationships** between entities.

#### ✅ Components:

1. **Entity**: A real-world object (e.g., Student, Book)

   - **Entity Set**: Collection of similar entities
   - **Types**:
     - **Strong Entity**: Has a primary key
     - **Weak Entity**: Depends on another entity (no sufficient key)

2. **Attribute**: Describes properties of an entity

   - Types:
     - **Simple** (atomic): `Name`
     - **Composite**: `Name → {First, Last}`
     - **Derived**: `Age` from DOB
     - **Multivalued**: `PhoneNumbers`

3. **Relationship**: Association between entities (e.g., Student ― Enrolls ― Course)

   - Degree: Unary, Binary, Ternary
   - Cardinality: 1:1, 1:N, M:N
   - Participation: Total vs Partial

4. **Keys**: Unique identifiers (e.g., RollNo for Student)

5. **Special Constructs**:
   - **Generalization**: Subclasses from superclasses
   - **Specialization**: Classifying entities
   - **Aggregation**: Relationship involving relationships

---

#### 🔍 ER Diagram (ASCII-style):

```
   +---------+       Enrolls      +--------+
   | Student | -----------------> | Course |
   +---------+                    +--------+
      |                               |
   RollNo, Name                    CID, Title
```

---

#### 📥 Example:

```text
Entity: Student
Attributes: RollNo (PK), Name, Age

Entity: Course
Attributes: CID (PK), Title

Relationship: Enrolls
Attributes: EnrollmentDate
Cardinality: M:N
```

---

#### 🌐 Real-World Q&A:

**Q:** Why use ER modeling?  
**A:** It gives a clear logical view before database schema is finalized.

**Q:** What happens after ER design?  
**A:** The ER diagram is **converted to relational schema** (tables with keys and constraints).

---

### 🔹 Document and Key-Value Models (NoSQL Context)

#### ✅ Definition:

These are **non-relational data models** commonly used in **NoSQL databases** for storing unstructured or semi-structured data.

---

### 📘 1. Document Model

#### ✅ Description:

Stores data as **documents**, typically in **JSON**, **BSON**, or **XML** format. Each document is a self-contained record with flexible schema.

#### 📥 Example (MongoDB-style):

```json
{
  "student_id": 101,
  "name": "Ayush",
  "courses": ["DBMS", "CN"],
  "contact": {
    "email": "ayush@example.com",
    "phone": "9876543210"
  }
}
```

#### 🔍 Diagram:

```
[Document: Student]
 ├── student_id: 101
 ├── name: "Ayush"
 ├── courses: ["DBMS", "CN"]
 └── contact:
       ├── email: ...
       └── phone: ...
```

#### ✅ Benefits:

- Schema-less
- Supports nested objects
- Fast read/write for hierarchical data

#### ✅ Use Cases:

- CMS, blogging platforms, user profiles, analytics

---

### 📘 2. Key-Value Model

#### ✅ Description:

Simplest form of NoSQL. Each item is stored as a **(key, value)** pair. The key is unique and used to retrieve the value directly.

#### 📥 Example (Redis-style):

```text
"username:101" → "Ayush"
"user:101:email" → "ayush@example.com"
"user:101:age" → "21"
```

#### 🔍 Diagram:

```
Key                    → Value
----------------------|-----------------------
"user:101:name"       → "Ayush"
"user:101:balance"    → "10000"
"product:567:stock"   → "14"
```

#### ✅ Benefits:

- Very fast (O(1) access)
- Perfect for caching, session management

#### ✅ Use Cases:

- Caches (Redis, Memcached)
- User session tokens
- Shopping cart items

---

#### 🌐 Real-World Q&A:

**Q:** Why prefer Document model over RDBMS for user profiles?  
**A:** User profiles have **variable fields** (e.g., preferences, settings) — flexible schema suits better.

**Q:** When to choose Key-Value store?  
**A:** When **speed and simplicity** matter more than relationships. Ideal for **caching** or **stateless session stores**.

**Q:** Can Document and Key-Value models handle joins?  
**A:** Not efficiently. These models often **duplicate data** to avoid joins and rely on **denormalization**.

---

#### 📊 Summary Table:

| Feature     | Document Store        | Key-Value Store         |
| ----------- | --------------------- | ----------------------- |
| Data Format | JSON, BSON            | String / Binary         |
| Querying    | Rich (fields, nested) | Key-based only          |
| Schema      | Flexible              | None                    |
| Speed       | Moderate              | Very High               |
| Use Case    | CMS, profiles, logs   | Caching, tokens, config |
| Example DBs | MongoDB, Couchbase    | Redis, Riak, DynamoDB   |

---

## 🔷 3. ER Model & Design

---

### 🔹 Entity & Entity Set

#### ✅ Definition:

- An **Entity** is a real-world object or concept that can be distinctly identified in a database.
- An **Entity Set** is a collection of similar entities.

#### 📥 Examples:

- Entity: `Student` with attributes like `RollNo`, `Name`
- Entity Set: All students in a university

#### 🔍 ER Representation:

```
   +----------+
   | Student  |
   +----------+
```

#### ✅ Types of Entities:

- **Strong Entity**: Has a primary key; independent.
- **Weak Entity**: Cannot be uniquely identified by its attributes alone; depends on a strong entity.
  - Must have a **partial key** and **identifying relationship**.

#### 📥 Example:

```
Strong Entity: Customer(CustomerID, Name)
Weak Entity:   Order(OrderID, Date) — needs CustomerID
```

#### 🌐 Real-World Q&A:

**Q:** Why distinguish weak entities?  
**A:** Helps model dependent data like installments, addresses, etc., where identity is only valid within a parent entity.

---

### 🔹 Attributes (Simple, Composite, Derived, Multivalued)

#### ✅ Types of Attributes:

| Type              | Description                | Example                      |
| ----------------- | -------------------------- | ---------------------------- |
| **Simple**        | Atomic, indivisible        | Age, RollNo                  |
| **Composite**     | Grouped attributes         | Name → {FirstName, LastName} |
| **Derived**       | Computable from other data | Age (from DOB)               |
| **Multivalued**   | Can have multiple values   | PhoneNumbers → {9876, 8765}  |
| **Key Attribute** | Identifies entity uniquely | RollNo in Student            |

#### 🔍 Diagram:

```
+----------+
| Student  |
+----------+
   |
   +-- RollNo (Key)
   +-- Name
   |     |
   |     +-- FirstName
   |     +-- LastName
   +-- DOB
   +-- Age (Derived)
   +-- PhoneNumbers (Multivalued)
```

#### 🌐 Real-World Q&A:

**Q:** How are multivalued attributes handled in RDBMS?  
**A:** Using **separate tables** (e.g., `StudentPhones(StudentID, Phone)`).

---

### 🔹 Relationships (Unary, Binary, Ternary)

#### ✅ Definition:

A **relationship** is an association between two or more entities.

#### ✅ Types:

| Relationship Type | Description                           | Example                           |
| ----------------- | ------------------------------------- | --------------------------------- |
| **Unary**         | Entity related to itself              | Employee manages Employee         |
| **Binary**        | Between two entity sets (most common) | Student enrolls in Course         |
| **Ternary**       | Among three entity sets               | Doctor prescribes Drug to Patient |

---

#### 🔍 Diagrams:

**Binary**:

```
+---------+    Enrolls    +--------+
| Student | ------------> | Course |
+---------+               +--------+
```

**Unary**:

```
   +---------+
   | Employee|
   +---------+
       |
     manages
       ↓
   +---------+
```

**Ternary**:

```
+--------+     +--------+     +---------+
| Doctor |-----| Drug   |-----| Patient |
+--------+     +--------+     +---------+
        \       Prescribes      /
         +---------------------+
```

---

#### 🌐 Real-World Q&A:

**Q:** Can ternary relationships be broken into binary ones?  
**A:** Not always safely. It may lead to **loss of information** or introduce **redundancy**.

---

### 🔹 Cardinality & Participation Constraints

#### ✅ Cardinality Constraints:

Specifies the number of entity instances that can participate in a relationship.

| Type | Meaning                   | Example                |
| ---- | ------------------------- | ---------------------- |
| 1:1  | One entity related to one | Person — Passport      |
| 1:N  | One to many               | Department — Employees |
| M:N  | Many to many              | Student — Course       |

---

#### ✅ Participation Constraints:

Defines **whether all entities must participate** in a relationship.

| Type        | Meaning                                                    |
| ----------- | ---------------------------------------------------------- |
| **Total**   | Every entity **must** participate (shown with double line) |
| **Partial** | Participation is **optional** (shown with single line)     |

---

#### 🔍 Example ER Diagram:

```
+------------+        WorksIn         +-------------+
|  Employee  |----------------------->| Department  |
+------------+                        +-------------+
   (Total)                              (Partial)
    1:N                                Each dept may have 0+ employees
```

---

#### 🌐 Real-World Q&A:

**Q:** Why use total participation?  
**A:** Enforces business rules like "Every employee must belong to some department".

**Q:** What’s the difference between cardinality and participation?  
**A:**

- **Cardinality**: Number of associations (1:1, M:N, etc.)
- **Participation**: Mandatory vs optional involvement of entities

---

### 🔹 Keys in ER (Super Key, Candidate Key, Primary Key, Foreign Key)

#### ✅ Definitions:

| Key Type          | Description                                                              |
| ----------------- | ------------------------------------------------------------------------ |
| **Super Key**     | Set of one or more attributes that uniquely identify an entity           |
| **Candidate Key** | Minimal Super Key (no extra attributes)                                  |
| **Primary Key**   | One of the candidate keys chosen to uniquely identify records            |
| **Foreign Key**   | Attribute in one entity that refers to the primary key of another entity |

---

#### 📥 Example:

Consider `Student(RollNo, Name, Email, Phone)`

- Super Keys: `{RollNo}`, `{RollNo, Name}`, `{Email}`
- Candidate Keys: `{RollNo}`, `{Email}`
- Primary Key: `{RollNo}` (chosen)
- Foreign Key: `Student.DepartmentID → Department.DeptID`

---

#### 🌐 Real-World Q&A:

**Q:** Can a relation have multiple candidate keys?  
**A:** Yes. Example: Email and RollNo both uniquely identify students.

**Q:** Can a foreign key be null?  
**A:** Yes, if the relationship is optional (partial participation).

---

### 🔹 Weak vs Strong Entity

#### ✅ Strong Entity:

- Has a primary key
- Independent — does not rely on any other entity

#### ✅ Weak Entity:

- Has no sufficient attributes to form a primary key
- Depends on a **strong entity**
- Has a **partial key** and **identifying relationship**

---

#### 📥 Example:

- Strong: `Customer(CustomerID, Name)`
- Weak: `Order(OrderNo, Date)` — identified as `(CustomerID, OrderNo)`

---

#### 🔍 Diagram:

```
+-------------+         Places        +---------+
|  Customer   |---------------------->|  Order  |
+-------------+                      /+---------+
    (PK)                             / (Partial Key: OrderNo)
                                   / (Double diamond)
```

---

#### 🌐 Real-World Q&A:

**Q:** How is a weak entity mapped to relational schema?  
**A:** Include primary key of strong entity + partial key of weak entity → Combined primary key.

---

### 🔹 Generalization, Specialization, Aggregation

#### ✅ Generalization:

- **Bottom-up** approach: Combine multiple entities into a **superclass**
- e.g., `Car` and `Truck` → `Vehicle`

#### ✅ Specialization:

- **Top-down** approach: Break a superclass into **subclasses**
- e.g., `Employee` → `Engineer`, `Manager`

#### 🔍 Diagram:

```
            Vehicle
           /       \
        Car        Truck
```

---

#### ✅ Aggregation:

- A **relationship** treated as an **abstract higher-level entity**
- Useful when a relationship participates in another relationship

#### 🔍 Example Diagram:

```
     +--------+         +---------+
     | Doctor |---------| Patient |
     +--------+         +---------+
          \               /
          Treats (Relationship)
              |
         +----------------+
         | Appointment     |
         +----------------+
         |
         Prescribes
         |
     +--------+
     |  Drug  |
     +--------+
```

Here, `Appointment` is an aggregation.

---

#### 🌐 Real-World Q&A:

**Q:** When is aggregation required?  
**A:** When a **relationship itself has relationships**, e.g., Doctor treating a Patient and prescribing drugs during that treatment.

---

### 🔹 Converting ER to Relational Schema

#### ✅ Mapping Rules:

1. **Entity Set** → Create a table with all attributes
2. **Relationship**:
   - **1:1** → Add foreign key in either table
   - **1:N** → Add foreign key in table on N side
   - **M:N** → Create a new table with foreign keys of both entities
3. **Multivalued Attributes** → Create separate table
4. **Weak Entity** → Create table with foreign key + partial key as primary key
5. **Specialization/Generalization**:
   - Option 1: One table per class (sub + super)
   - Option 2: One table per subclass only
   - Option 3: One big table with all attributes (nulls allowed)

---

#### 📥 Example:

**ER Design**:

- `Student(RollNo, Name)`
- `Course(CID, Title)`
- Relationship: `Enrolls(Student, Course, Grade)` — M:N

**Relational Schema**:

```sql
Student(RollNo PRIMARY KEY, Name)
Course(CID PRIMARY KEY, Title)
Enrolls(RollNo FOREIGN KEY, CID FOREIGN KEY, Grade)
PRIMARY KEY (RollNo, CID)
```

---

#### 🌐 Real-World Q&A:

**Q:** Why convert ER to relational schema?  
**A:** SQL operates on relations (tables), so the conceptual ER model must be transformed into a relational form for implementation.

**Q:** What happens to derived attributes?  
**A:** They are typically **not stored**, but computed when needed.

---

## 🔷 4. Relational Model

---

### 🔹 Structure of a Relational Table

#### ✅ Definition:

A **relational table** represents a relation in a relational database. It is a **2D structure** consisting of:

- **Rows (Tuples)**: Represent individual records
- **Columns (Attributes)**: Represent data fields

Each table is defined by a **schema** and stores actual data (instances).

---

#### 📥 Example:

```text
Table: Employee

+--------+----------+---------+-----------+
| EmpID  | Name     | Age     | DeptID    |
+--------+----------+---------+-----------+
| 101    | Ayush    | 28      | D001      |
| 102    | Priya    | 32      | D002      |
+--------+----------+---------+-----------+
```

---

#### 🔍 ASCII Diagram:

```
         +------------------------------+
         |         Employee             |
         +--------+--------+-----+------+
         | EmpID  | Name   | Age | Dept |
         +--------+--------+-----+------+
         |  101   | Ayush  | 28  | D001 |
         |  102   | Priya  | 32  | D002 |
         +--------+--------+-----+------+
```

---

#### 🌐 Real-World Q&A:

**Q:** Why is data stored in a tabular format?  
**A:** It allows relational operations like joins, filters, and projections to be easily applied using set theory and SQL.

---

### 🔹 Tuple, Attribute, Relation

#### ✅ Definitions:

- **Attribute**: A column in a relation (e.g., `Name`, `Age`)
- **Tuple**: A row in a relation (e.g., entire record of `EmpID = 101`)
- **Relation**: A complete table (set of tuples and attributes)

#### 📥 Example:

```text
Tuple: (101, Ayush, 28, D001)
Attribute: Age
Relation: Employee Table
```

---

#### 🌐 Real-World Q&A:

**Q:** Are tuples ordered in a relation?  
**A:** No. Mathematically, a relation is a set of tuples, so order does **not** matter.

**Q:** Can attribute values be repeated?  
**A:** Yes, unless uniqueness constraints (like PRIMARY KEY or UNIQUE) are specified.

---

### 🔹 Domain, Degree, Cardinality

#### ✅ Domain:

- The **data type or permissible values** of an attribute
- e.g., Age → integer between 0 and 120

#### ✅ Degree:

- Number of **attributes (columns)** in a relation
- e.g., `Employee(EmpID, Name, Age, DeptID)` → Degree = 4

#### ✅ Cardinality:

- Number of **tuples (rows)** in a relation
- e.g., If Employee has 100 records → Cardinality = 100

---

#### 📥 Example:

```text
Relation: Student(RollNo, Name, Age)

Domain:
  - RollNo: Integer
  - Name: String
  - Age: Integer (0–120)

Degree: 3
Cardinality: 5 (if 5 rows present)
```

---

#### 🌐 Real-World Q&A:

**Q:** Can two attributes in the same relation have the same domain?  
**A:** Yes. E.g., both `Age` and `Experience` might be of type INTEGER.

**Q:** Can domain constraints enforce business rules?  
**A:** Yes. Domains can restrict values (e.g., `Grade` ∈ {A, B, C, D, F}).

---

### 🔹 Integrity Constraints

#### ✅ Definition:

**Integrity Constraints** are rules that maintain the **accuracy, correctness, and consistency** of the data in a relational database.

---

### 🔸 1. Domain Constraint

#### ✅ Definition:

A **Domain Constraint** specifies that the value of each attribute must be from a **predefined domain (data type and valid range/format)**.

#### 📥 Example:

```sql
Age INTEGER CHECK (Age >= 0 AND Age <= 120)
Email VARCHAR(100)
Gender ENUM('Male', 'Female', 'Other')
```

#### ✅ Violation:

```sql
-- Invalid entry: Age = -5
INSERT INTO Student VALUES (101, 'Ayush', -5);
-- ❌ Domain constraint violated
```

#### 🌐 Real-World Q&A:

**Q:** Can domain constraints be customized beyond data types?  
**A:** Yes, using `CHECK` and ENUMs for additional logic.

---

### 🔸 2. Entity Integrity Constraint

#### ✅ Definition:

Ensures that the **primary key** of a relation is **not NULL and uniquely identifies** each tuple.

#### 📥 Example:

```sql
CREATE TABLE Employee (
  EmpID INT PRIMARY KEY,  -- Not Null + Unique
  Name VARCHAR(50)
);
```

#### ❌ Violations:

- Inserting a duplicate `EmpID`
- Inserting NULL into `EmpID`

```sql
-- Invalid: NULL primary key
INSERT INTO Employee VALUES (NULL, 'Priya');

-- Invalid: Duplicate EmpID
INSERT INTO Employee VALUES (101, 'Ayush');
INSERT INTO Employee VALUES (101, 'Ravi');
```

#### 🌐 Real-World Q&A:

**Q:** Why must the primary key be non-null?  
**A:** Because it's used to **uniquely identify** each row; NULL means "unknown", which breaks identity.

---

### 🔸 3. Referential Integrity Constraint

#### ✅ Definition:

Ensures that a **foreign key** in one relation must **match a primary key** in another relation or be NULL (in case of optional relationships).

#### 📥 Example:

```sql
CREATE TABLE Department (
  DeptID INT PRIMARY KEY,
  DeptName VARCHAR(50)
);

CREATE TABLE Employee (
  EmpID INT PRIMARY KEY,
  Name VARCHAR(50),
  DeptID INT,
  FOREIGN KEY (DeptID) REFERENCES Department(DeptID)
);
```

#### ❌ Violation:

```sql
-- Fails if DeptID 999 does not exist
INSERT INTO Employee VALUES (102, 'Riya', 999);
```

---

#### 🌐 Real-World Q&A:

**Q:** What happens when a referenced row is deleted?  
**A:** Depends on action:

- `ON DELETE CASCADE` → deletes dependent rows
- `ON DELETE SET NULL` → sets FK to NULL
- `ON DELETE RESTRICT` (default) → throws error

---

### 🔹 Schema Diagrams

#### ✅ Definition:

A **Schema Diagram** is a graphical representation of the structure of a relational database, including:

- Tables (relations)
- Attributes
- Primary and foreign keys
- Relationships between tables

---

#### 🔍 ASCII Diagram:

```
  +------------+           +--------------+
  |  Employee  |           |  Department  |
  +------------+           +--------------+
  | EmpID (PK) |           | DeptID (PK)  |
  | Name       |           | DeptName     |
  | DeptID (FK)|-----------|              |
  +------------+           +--------------+
```

- `EmpID` is the primary key of `Employee`
- `DeptID` is both:
  - Primary key in `Department`
  - Foreign key in `Employee`

---

#### 🌐 Real-World Q&A:

**Q:** How are schema diagrams useful in database design?  
**A:** They provide a **visual overview** of table relationships, making it easier to understand joins, integrity rules, and entity links.

**Q:** Are schema diagrams used in ER modeling or implementation?  
**A:** They are **used post-ER modeling**, after converting ER diagrams to relational schema.

---

## 🔷 5. Relational Algebra & Relational Calculus

---

### 🔹 Relational Algebra Overview

#### ✅ Definition:

**Relational Algebra** is a **procedural query language** that uses mathematical operators to retrieve and manipulate data from relational databases. It operates on **relations (tables)** and produces **new relations** as output.

#### ✅ Notation:

- `σ`: Selection
- `π`: Projection
- `×`: Cartesian Product
- `∪`: Union
- `∩`: Intersection
- `−`: Set Difference
- `ρ`: Rename

---

### 🔸 1. Selection (σ)

#### ✅ Purpose:

Extracts rows (tuples) from a relation that **satisfy a given condition**.

#### 📥 Syntax:

```text
σ<condition>(Relation)
```

#### 📥 Example:

```text
σAge > 25(Employee)
```

Returns all employees older than 25.

---

#### 🔍 Table Example:

```
Employee
+--------+--------+-----+
| EmpID  | Name   | Age |
+--------+--------+-----+
| 101    | Ayush  | 28  |
| 102    | Riya   | 24  |
+--------+--------+-----+

σAge > 25(Employee)
→
+--------+--------+-----+
| 101    | Ayush  | 28  |
+--------+--------+-----+
```

---

### 🔸 2. Projection (π)

#### ✅ Purpose:

Selects **specific columns (attributes)** from a relation.

#### 📥 Syntax:

```text
π<attribute_list>(Relation)
```

#### 📥 Example:

```text
πName, Age(Employee)
```

---

#### 🔍 Output:

```
+--------+-----+
| Name   | Age |
+--------+-----+
| Ayush  | 28  |
| Riya   | 24  |
+--------+-----+
```

---

### 🔸 3. Cartesian Product (×)

#### ✅ Purpose:

Combines **every tuple of one relation with every tuple of another**.

#### 📥 Syntax:

```text
R × S
```

#### 📥 Example:

```text
Employee × Department
```

If `Employee` has 3 rows and `Department` has 2 → result has 3×2 = 6 rows.

---

#### ⚠️ Note:

Useful as an intermediate step in **JOIN** operations, but rarely used directly.

---

### 🔸 4. Union (∪)

#### ✅ Purpose:

Returns all **distinct tuples** that are present in either of the two relations.

#### 📥 Syntax:

```text
R ∪ S
```

- Relations must be **union-compatible**:
  - Same number of attributes
  - Corresponding attributes have same domains

#### 📥 Example:

```
πName(Student) ∪ πName(Teacher)
```

---

### 🔸 5. Intersection (∩)

#### ✅ Purpose:

Returns tuples that are **common to both relations**.

#### 📥 Syntax:

```text
R ∩ S
```

- Also requires **union compatibility**

---

#### 📥 Example:

```
πCourse(Student) ∩ πCourse(Teacher)
```

Returns courses taught by teachers and taken by students.

---

### 🔸 6. Set Difference (−)

#### ✅ Purpose:

Returns tuples that are in the **first relation but not in the second**.

#### 📥 Syntax:

```text
R − S
```

#### 📥 Example:

```text
πName(Student) − πName(Alumni)
```

Returns students who are not alumni.

---

### 🔸 7. Rename (ρ)

#### ✅ Purpose:

Changes the **name of a relation or its attributes**.

#### 📥 Syntax:

```text
ρ(NewName, OldRelation)
ρ(NewName(A1, A2...), OldRelation)
```

#### 📥 Example:

```text
ρ(Emp, Employee)
ρ(Emp(EID, EName, Age), Employee)
```

---

#### 🌐 Real-World Q&A:

**Q:** Why use Relational Algebra if we have SQL?  
**A:** Relational Algebra is used for **theoretical foundations**, **query optimization**, and building **query engines** under the hood.

**Q:** Can relational algebra queries be nested?  
**A:** Yes. Like functions, outputs of one operator can feed into another:

```text
πName(σAge > 25(Employee))
```

---

### 🔹 Join Operations (Theta Join, Natural Join, Outer Join, Semi Join)

---

### 🔸 1. Theta Join (θ Join)

#### ✅ Definition:

A **Theta Join** combines tuples from two relations based on a **general condition** (not necessarily equality).

#### 📥 Syntax:

```text
R ⋈θ S
```

Where `θ` is a condition like `R.A < S.B`

#### 📥 Example:

```text
Employee ⋈ Employee.DeptID = Department.DeptID Department
```

---

### 🔸 2. Natural Join

#### ✅ Definition:

A special case of **Theta Join** where the join is done **automatically on all attributes with the same name** and removes duplicate columns.

#### 📥 Syntax:

```text
R ⋈ S
```

#### 📥 Example:

```text
Employee ⋈ Department
```

If both have `DeptID`, they will be joined on `DeptID`.

---

### 🔸 3. Outer Joins (Left, Right, Full)

#### ✅ Definition:

Returns all matched tuples + **unmatched tuples padded with NULLs**.

| Type        | Description                          |
| ----------- | ------------------------------------ |
| Left Outer  | All from left + matched from right   |
| Right Outer | All from right + matched from left   |
| Full Outer  | All from both; unmatched rows → NULL |

---

#### 📥 Example:

```text
Employee ⟕ Department   -- Left Outer Join
Employee ⟖ Department   -- Right Outer Join
Employee ⟗ Department   -- Full Outer Join
```

---

### 🔸 4. Semi Join

#### ✅ Definition:

Returns **only the left relation tuples** that have a match in the right relation — like a filter.

#### 📥 Syntax:

```text
R ▷ S
```

---

#### 📥 Example:

```text
πEmpID(Employee ⋈ Department)
```

OR use:

```text
Employee ▷ Department
```

Returns employees who work in some department — but shows only employee data.

---

#### 🌐 Real-World Q&A:

**Q:** When is Semi Join useful?  
**A:** In **distributed databases** — it reduces data transfer by sending only necessary tuples.

**Q:** Can Outer Joins be simulated using Relational Algebra?  
**A:** Yes, but it's complex and requires unions, difference, and null padding.

---

### 🔹 Division Operator

#### ✅ Definition:

The **Division operator** is used when we want to find entities related to **all values** in another set.

#### 📥 Syntax:

```text
R ÷ S
```

- `R(A, B)` and `S(B)` → Result: all `A` values that are related to **every B in S**

---

#### 📥 Example:

```text
R = StudentCourse(StudentID, CourseID)
S = RequiredCourses(CourseID)

Query: Find all students who have taken **all required courses**
→ StudentCourse ÷ RequiredCourses
```

---

#### 🌐 Real-World Q&A:

**Q:** Is division common in SQL?  
**A:** No, SQL doesn’t have direct division; it's emulated using **nested NOT EXISTS / GROUP BY HAVING COUNT**.

---

### 🔹 Relational Calculus

#### ✅ Definition:

A **non-procedural query language** — focuses on **what to retrieve**, not **how to retrieve** it.

---

### 🔸 Tuple Relational Calculus (TRC)

#### ✅ Syntax:

```text
{ t | P(t) }
```

- `t` is a tuple variable
- `P(t)` is a predicate

---

#### 📥 Example:

```text
{ t | t ∈ Employee ∧ t.Age > 25 }
```

Returns all employee tuples where age > 25.

---

### 🔸 Domain Relational Calculus (DRC)

#### ✅ Syntax:

```text
{ <x1, x2, ... xn> | P(x1, x2, ..., xn) }
```

- Uses **attribute-level variables**

---

#### 📥 Example:

```text
{ <n, a> | ∃i (Employee(i, n, a, d) ∧ a > 25) }
```

Returns name and age of employees older than 25.

---

### 🔹 Expressing Queries in Relational Algebra and Calculus

---

#### 📥 Example Query:

**Query**: Find names of employees in department 'D001'

---

**Relational Algebra**:

```text
πName(σDeptID = 'D001'(Employee))
```

---

**Tuple Relational Calculus**:

```text
{ t.Name | t ∈ Employee ∧ t.DeptID = 'D001' }
```

---

**Domain Relational Calculus**:

```text
{ <n> | ∃i, a, d (Employee(i, n, a, d) ∧ d = 'D001') }
```

---

#### 🌐 Real-World Q&A:

**Q:** Which is used internally by DBMS: algebra or calculus?  
**A:** **Relational Algebra** is used for **query optimization and execution**. Calculus is more for theory and validation.

**Q:** Can all relational algebra queries be expressed in calculus?  
**A:** Yes — both are **equally expressive** (relationally complete), though styles differ.

---

## 🔷 6. SQL (Structured Query Language)

---

### 🔸 CREATE, INSERT, UPDATE, DELETE, SELECT

#### ✅ CREATE

Used to **define new tables** or database objects.

```sql
CREATE TABLE Employee (
  EmpID INT PRIMARY KEY,
  Name VARCHAR(50),
  Age INT,
  DeptID INT
);
```

---

#### ✅ INSERT

Used to **insert new records** into a table.

```sql
INSERT INTO Employee (EmpID, Name, Age, DeptID)
VALUES (101, 'Ayush', 28, 1);
```

---

#### ✅ UPDATE

Used to **modify existing records**.

```sql
UPDATE Employee
SET Age = 29
WHERE EmpID = 101;
```

---

#### ✅ DELETE

Used to **remove rows** from a table.

```sql
DELETE FROM Employee
WHERE Age < 20;
```

---

#### ✅ SELECT

Used to **retrieve data** from a table.

```sql
SELECT * FROM Employee;
SELECT Name, Age FROM Employee;
```

---

📤 Sample Output:

```text
+--------+--------+-----+
| Name   | Age    |     |
+--------+--------+-----+
| Ayush  | 29     |     |
| Riya   | 26     |     |
+--------+--------+-----+
```

---

### 🔸 WHERE, ORDER BY, GROUP BY, HAVING

#### ✅ WHERE

Filters rows based on conditions.

```sql
SELECT * FROM Employee WHERE Age > 25;
```

---

#### ✅ ORDER BY

Sorts the result set.

```sql
SELECT * FROM Employee ORDER BY Age DESC;
```

---

#### ✅ GROUP BY

Groups rows with the same values.

```sql
SELECT DeptID, COUNT(*) FROM Employee GROUP BY DeptID;
```

---

#### ✅ HAVING

Filters groups (used with GROUP BY).

```sql
SELECT DeptID, COUNT(*)
FROM Employee
GROUP BY DeptID
HAVING COUNT(*) > 5;
```

---

### 🔸 DISTINCT, LIKE, BETWEEN, IN, IS NULL

#### ✅ DISTINCT

Removes duplicate values.

```sql
SELECT DISTINCT DeptID FROM Employee;
```

---

#### ✅ LIKE

Pattern matching using wildcards (`%`, `_`).

```sql
SELECT * FROM Employee WHERE Name LIKE 'A%';
```

---

#### ✅ BETWEEN

Range filtering (inclusive).

```sql
SELECT * FROM Employee WHERE Age BETWEEN 25 AND 35;
```

---

#### ✅ IN

Matches values in a list.

```sql
SELECT * FROM Employee WHERE DeptID IN (1, 2, 3);
```

---

#### ✅ IS NULL / IS NOT NULL

Checks for null values.

```sql
SELECT * FROM Employee WHERE DeptID IS NULL;
```

---

### 🔸 LIMIT, OFFSET

#### ✅ LIMIT

Restricts number of rows returned.

```sql
SELECT * FROM Employee LIMIT 5;
```

---

#### ✅ OFFSET

Skips a number of rows before starting to return rows.

```sql
SELECT * FROM Employee LIMIT 5 OFFSET 10;
```

---

#### 🌐 Real-World Q&A:

**Q:** What’s the difference between WHERE and HAVING?  
**A:** `WHERE` filters rows **before** grouping; `HAVING` filters **after GROUP BY**.

**Q:** Why use OFFSET and LIMIT in pagination?  
**A:** To load data in pages — e.g., showing 10 results at a time in UI tables.

**Q:** Can LIMIT be used with ORDER BY?  
**A:** Yes, to fetch **top-N** records:

```sql
SELECT * FROM Employee ORDER BY Age DESC LIMIT 3;
```

---

### 🔹 SQL Joins

---

### 🔸 INNER JOIN

#### ✅ Definition:

Returns only the **matching rows** from both tables based on the specified join condition.

#### 💻 Syntax:

```sql
SELECT *
FROM Employee e
INNER JOIN Department d ON e.DeptID = d.DeptID;
```

#### 📥 Example:

```
Employee Table
+--------+--------+--------+
| EmpID  | Name   | DeptID |
+--------+--------+--------+
| 101    | Ayush  | 1      |
| 102    | Riya   | 2      |
+--------+--------+--------+

Department Table
+--------+-------------+
| DeptID | DeptName    |
+--------+-------------+
| 1      | HR          |
| 3      | Finance     |
+--------+-------------+

Result:
+--------+--------+--------+--------+-----------+
| EmpID  | Name   | DeptID | DeptID | DeptName  |
+--------+--------+--------+--------+-----------+
| 101    | Ayush  | 1      | 1      | HR        |
+--------+--------+--------+--------+-----------+
```

---

### 🔸 LEFT, RIGHT, FULL OUTER JOIN

#### ✅ LEFT OUTER JOIN:

Returns **all rows from left** table + matched rows from right (NULL if no match).

```sql
SELECT *
FROM Employee e
LEFT JOIN Department d ON e.DeptID = d.DeptID;
```

---

#### ✅ RIGHT OUTER JOIN:

Returns **all rows from right** table + matched rows from left (NULL if no match).

```sql
SELECT *
FROM Employee e
RIGHT JOIN Department d ON e.DeptID = d.DeptID;
```

---

#### ✅ FULL OUTER JOIN:

Returns **all rows from both** tables with NULLs where no match exists.

```sql
SELECT *
FROM Employee e
FULL OUTER JOIN Department d ON e.DeptID = d.DeptID;
```

---

### 🔸 SELF JOIN

#### ✅ Definition:

A join of a table **with itself**. Useful for hierarchical or comparative data.

#### 💻 Syntax:

```sql
SELECT A.Name AS Employee, B.Name AS Manager
FROM Employee A
JOIN Employee B ON A.ManagerID = B.EmpID;
```

---

#### 📥 Example:

Find employees and their managers from the same `Employee` table.

---

### 🔸 CROSS JOIN

#### ✅ Definition:

Returns **Cartesian product**: each row of the first table joined with every row of the second.

#### 💻 Syntax:

```sql
SELECT * FROM Employee CROSS JOIN Department;
```

If Employee has 3 rows and Department has 2 → Result: 6 rows.

---

### 🔸 NATURAL JOIN

#### ✅ Definition:

A type of inner join that **automatically matches columns** with **same name and data type**, and eliminates duplicate columns.

#### 💻 Syntax:

```sql
SELECT * FROM Employee NATURAL JOIN Department;
```

⚠️ Use with caution — can lead to unexpected results if column names overlap unintentionally.

---

### 🔍 ASCII Join Illustration:

```
INNER JOIN
  A ∩ B

LEFT JOIN
  A ⟕ B

RIGHT JOIN
  A ⟖ B

FULL JOIN
  A ⟗ B

SELF JOIN
  A ⋈ A (Alias)

CROSS JOIN
  A × B

NATURAL JOIN
  A ⋈ (matched cols)
```

---

### 🌐 Real-World Q&A:

**Q:** What's the difference between INNER and LEFT JOIN?  
**A:** INNER JOIN shows only matching rows; LEFT JOIN shows all rows from the left table + matched data.

**Q:** When is SELF JOIN used?  
**A:** For hierarchical data — like employees reporting to other employees.

**Q:** Why is CROSS JOIN rarely used in production?  
**A:** It creates **explosive row combinations** — use only when needed explicitly (e.g., generating all combinations).

**Q:** Can NATURAL JOIN be dangerous?  
**A:** Yes. It joins on all **matching column names**, which can cause accidental data joins.

---

### 🔹 SQL Subqueries

---

### 🔸 What is a Subquery?

#### ✅ Definition:

A **subquery** is a SQL query embedded inside another query. It is often enclosed in parentheses and can be used in `SELECT`, `FROM`, or `WHERE` clauses.

---

### 🔸 1. Scalar Subquery

#### ✅ Definition:

Returns a **single value** (one row, one column).

#### 💻 Example:

```sql
SELECT Name
FROM Employee
WHERE Age = (SELECT MAX(Age) FROM Employee);
```

Returns the name of the oldest employee.

📤 Output:

```text
+--------+
| Name   |
+--------+
| Ayush  |
+--------+
```

---

### 🔸 2. Nested Subquery

#### ✅ Definition:

A subquery that is **independent** of the outer query. Evaluated **once**.

#### 💻 Example:

```sql
SELECT Name
FROM Employee
WHERE DeptID IN (
  SELECT DeptID FROM Department WHERE DeptName = 'HR'
);
```

---

### 🔸 3. Correlated Subquery

#### ✅ Definition:

A subquery that **depends on the outer query** for its value. It is evaluated **once for each row** of the outer query.

#### 💻 Example:

```sql
SELECT e.Name
FROM Employee e
WHERE Age > (
  SELECT AVG(Age)
  FROM Employee x
  WHERE x.DeptID = e.DeptID
);
```

Returns employees older than the average age of their department.

---

### 🔹 EXISTS vs IN vs ANY vs ALL

---

### 🔸 EXISTS

#### ✅ Definition:

Checks for the **existence of rows** returned by a subquery. Returns TRUE if subquery returns at least one row.

#### 💻 Example:

```sql
SELECT Name
FROM Employee e
WHERE EXISTS (
  SELECT 1 FROM Department d WHERE e.DeptID = d.DeptID
);
```

Returns employees who are assigned to valid departments.

---

### 🔸 IN

#### ✅ Definition:

Checks if a value **matches any value in a subquery result**.

#### 💻 Example:

```sql
SELECT Name
FROM Employee
WHERE DeptID IN (
  SELECT DeptID FROM Department WHERE Location = 'Delhi'
);
```

---

### 🔸 ANY

#### ✅ Definition:

Compares value with **any value** from a subquery result using a comparison operator.

#### 💻 Example:

```sql
SELECT Name
FROM Employee
WHERE Age > ANY (
  SELECT Age FROM Employee WHERE DeptID = 2
);
```

Returns employees older than **at least one** employee in Dept 2.

---

### 🔸 ALL

#### ✅ Definition:

Compares value with **all values** from subquery result.

#### 💻 Example:

```sql
SELECT Name
FROM Employee
WHERE Age > ALL (
  SELECT Age FROM Employee WHERE DeptID = 2
);
```

Returns employees older than **all** employees in Dept 2.

---

### 🌐 Real-World Q&A:

**Q:** When to use EXISTS over IN?  
**A:** Use `EXISTS` when you only need to **check existence**, not return values — especially **with correlated subqueries**.

**Q:** Difference between ANY and ALL?  
**A:**

- `> ANY`: greater than **minimum**
- `> ALL`: greater than **maximum**

**Q:** Why prefer scalar subqueries in SELECT clause?  
**A:** To **fetch derived values per row**, like total salary per department.

---

### 🔹 Advanced SQL

---

### 🔸 Aggregation Functions: COUNT, SUM, AVG, MAX, MIN

#### ✅ Definition:

Used to perform calculations over a set of values.

```sql
SELECT COUNT(*) FROM Employee;
SELECT AVG(Age) FROM Employee;
SELECT MAX(Salary), MIN(Salary) FROM Employee;
SELECT SUM(Salary) FROM Employee WHERE DeptID = 2;
```

---

### 🔸 CASE Statements

#### ✅ Definition:

Provides **conditional logic** in SQL queries.

```sql
SELECT Name,
  CASE
    WHEN Age < 25 THEN 'Junior'
    WHEN Age BETWEEN 25 AND 40 THEN 'Mid-Level'
    ELSE 'Senior'
  END AS Category
FROM Employee;
```

---

### 🔸 COALESCE, NULLIF

#### ✅ COALESCE:

Returns **first non-NULL** argument.

```sql
SELECT COALESCE(Email, 'N/A') FROM Employee;
```

#### ✅ NULLIF:

Returns NULL if two values are **equal**, otherwise returns the first.

```sql
SELECT NULLIF(Score, 0) FROM ExamResults;
```

---

### 🔸 Window Functions

#### ✅ Definition:

Operates on a set of rows **related to the current row** without collapsing rows.

```sql
SELECT Name, Salary,
  RANK() OVER (ORDER BY Salary DESC) AS SalaryRank,
  ROW_NUMBER() OVER (PARTITION BY DeptID ORDER BY Salary DESC) AS RowNum
FROM Employee;
```

| Function       | Use Case                           |
| -------------- | ---------------------------------- |
| `ROW_NUMBER()` | Unique row ID per partition        |
| `RANK()`       | Ranking with gaps                  |
| `DENSE_RANK()` | Ranking without gaps               |
| `LEAD()`       | Next row’s value                   |
| `LAG()`        | Previous row’s value               |
| `NTILE(n)`     | Divide rows into `n` equal buckets |

---

### 🔸 Common Table Expressions (CTE), WITH Clause

#### ✅ Definition:

A **temporary named result set** that can be referenced within a SQL statement.

```sql
WITH HighEarners AS (
  SELECT * FROM Employee WHERE Salary > 100000
)
SELECT Name FROM HighEarners;
```

✅ Improves readability, especially in **recursive queries**.

---

### 🔸 Views (CREATE, DROP, Updateable Views)

#### ✅ Definition:

A **virtual table** defined by a query. Helps with abstraction and security.

```sql
CREATE VIEW ActiveEmployees AS
SELECT Name, DeptID FROM Employee WHERE Status = 'Active';

DROP VIEW ActiveEmployees;
```

✅ A **simple view** (based on one table, no GROUP BY or joins) is **updateable**.

---

### 🔸 Indexing in SQL (Create, Drop)

#### ✅ Definition:

Improves **query performance** by speeding up data lookups.

```sql
CREATE INDEX idx_dept ON Employee(DeptID);
DROP INDEX idx_dept;
```

⚠️ Too many indexes can slow down INSERT/UPDATE due to maintenance overhead.

---

### 🔸 Triggers

#### ✅ Definition:

A trigger is a block of SQL that is **automatically executed** in response to certain events (INSERT, UPDATE, DELETE).

```sql
CREATE TRIGGER before_insert_emp
BEFORE INSERT ON Employee
FOR EACH ROW
BEGIN
  SET NEW.CreatedAt = CURRENT_DATE;
END;
```

✅ Used for **auditing**, **validation**, **logging**, **enforcement** of business rules.

---

### 🔸 Stored Procedures and Functions

#### ✅ Stored Procedure:

Reusable logic block — can include control flow, loops, conditionals.

```sql
CREATE PROCEDURE GetHighEarners()
BEGIN
  SELECT * FROM Employee WHERE Salary > 100000;
END;
```

#### ✅ Function:

Returns a value — used in SELECT or WHERE clauses.

```sql
CREATE FUNCTION GetAge(birthDate DATE)
RETURNS INT
BEGIN
  RETURN TIMESTAMPDIFF(YEAR, birthDate, CURDATE());
END;
```

---

### 🔸 Transactions (BEGIN, COMMIT, ROLLBACK)

#### ✅ Definition:

A transaction is a **sequence of operations** that execute as a single unit, following **ACID** properties.

```sql
BEGIN;
UPDATE Account SET Balance = Balance - 1000 WHERE AccID = 1;
UPDATE Account SET Balance = Balance + 1000 WHERE AccID = 2;
COMMIT;
```

✅ Use `ROLLBACK` to undo changes if something fails.

---

### 🔸 Constraints

| Constraint    | Description                             | Example                            |
| ------------- | --------------------------------------- | ---------------------------------- |
| `PRIMARY KEY` | Uniquely identifies rows                | `EmpID INT PRIMARY KEY`            |
| `FOREIGN KEY` | References another table                | `DeptID INT REFERENCES Department` |
| `UNIQUE`      | Ensures uniqueness (not necessarily PK) | `Email VARCHAR(100) UNIQUE`        |
| `CHECK`       | Validates condition per row             | `CHECK (Age >= 18)`                |
| `DEFAULT`     | Sets default value                      | `Status VARCHAR DEFAULT 'Active'`  |
| `NOT NULL`    | Prevents null values                    | `Name VARCHAR(50) NOT NULL`        |

---

### 🌐 Real-World Q&A

**Q:** Why use window functions over GROUP BY?  
**A:** Window functions let you **retain individual rows** while aggregating — useful for rankings, comparisons.

**Q:** When should you use views?  
**A:** To **simplify complex queries**, restrict access, or **abstract underlying logic**.

**Q:** Can stored procedures contain transactions?  
**A:** Yes — they often wrap critical operations in `BEGIN ... COMMIT`.

**Q:** Should every table have an index?  
**A:** Not necessarily. Index only **frequently queried** or **searched** columns.

---

## 🔷 7. Keys and Constraints

---

### 🔸 Super Key, Candidate Key

#### ✅ Super Key:

A **set of one or more attributes** that can uniquely identify a tuple (row) in a relation.

#### ✅ Candidate Key:

A **minimal super key** — removing any attribute breaks its uniqueness.

---

#### 📥 Example:

```text
Student(RollNo, Name, Email)

Super Keys:
- {RollNo}
- {Email}
- {RollNo, Email}
- {RollNo, Name}

Candidate Keys:
- {RollNo}
- {Email}
```

- `RollNo` and `Email` both can uniquely identify a student, so both are **candidate keys**.

---

#### 🔍 Diagram:

```
Super Keys (many)
 └── Candidate Keys (minimal)
       └── Primary Key (chosen one)
```

---

### 🔸 Primary Key

#### ✅ Definition:

A **candidate key chosen by the database designer** to uniquely identify records. It:

- Must be **unique**
- Cannot be **NULL**

---

#### 📥 Example:

```sql
CREATE TABLE Student (
  RollNo INT PRIMARY KEY,
  Name VARCHAR(50)
);
```

---

#### 🌐 Real-World Q&A:

**Q:** Why can't a primary key be NULL?  
**A:** It must uniquely identify every record. NULL represents "unknown", breaking uniqueness.

---

### 🔸 Alternate Key

#### ✅ Definition:

A **candidate key not chosen** as the primary key.

---

#### 📥 Example:

```text
Student(RollNo, Email, Name)

Candidate Keys: {RollNo}, {Email}

Primary Key: RollNo
→ Alternate Key: Email
```

---

### 🔸 Foreign Key

#### ✅ Definition:

An attribute in one table that **references the primary key** of another table.

- Enforces **referential integrity**
- Can be NULL if the relationship is optional

---

#### 📥 Example:

```sql
CREATE TABLE Department (
  DeptID INT PRIMARY KEY,
  DeptName VARCHAR(50)
);

CREATE TABLE Employee (
  EmpID INT PRIMARY KEY,
  Name VARCHAR(50),
  DeptID INT,
  FOREIGN KEY (DeptID) REFERENCES Department(DeptID)
);
```

---

#### 🔍 Diagram:

```
+------------+         +-------------+
|  Employee  |         |  Department |
|------------|         |-------------|
| EmpID (PK) |         | DeptID (PK) |
| DeptID (FK)| ------> | DeptID      |
+------------+         +-------------+
```

---

#### 🌐 Real-World Q&A:

**Q:** What happens if a referenced department is deleted?  
**A:** Depends on constraint:

- `ON DELETE CASCADE`: deletes matching employees
- `ON DELETE SET NULL`: sets `DeptID` to NULL
- Default: error if rows still exist in child table

---

### 🔸 Composite Key

#### ✅ Definition:

A **primary key composed of two or more attributes**.

Used when **no single attribute** is unique by itself.

---

#### 📥 Example:

```sql
CREATE TABLE Enrollment (
  StudentID INT,
  CourseID INT,
  EnrollmentDate DATE,
  PRIMARY KEY (StudentID, CourseID)
);
```

Each student can enroll in multiple courses; a unique enrollment is defined by the combination of both.

---

#### 🔍 Visual:

```
Enrollment(StudentID, CourseID, Date)

Composite Primary Key:
→ (StudentID, CourseID)
```

---

#### 🌐 Real-World Q&A:

**Q:** Can a composite key include a foreign key?  
**A:** Yes — often both attributes in the composite key reference other tables.

**Q:** Why use composite keys instead of surrogate keys?  
**A:** Composite keys enforce **real-world constraints**, reducing data anomalies.

---

### 🔸 Unique Key

#### ✅ Definition:

A **unique key** constraint ensures that **all values in a column or set of columns are distinct**, but **unlike primary keys**, it **can allow NULLs** (typically one NULL in most DBMSs).

---

#### 📥 Example:

```sql
CREATE TABLE Users (
  UserID INT PRIMARY KEY,
  Email VARCHAR(100) UNIQUE,
  Phone VARCHAR(15) UNIQUE
);
```

- Ensures no duplicate `Email` or `Phone` exists across records.
- NULLs are allowed (except in primary key).

---

#### 🔍 Diagram:

```
Users(UserID PK, Email UNIQUE, Phone UNIQUE)

• UserID   → Cannot be NULL and must be unique
• Email    → Must be unique (can be NULL)
• Phone    → Must be unique (can be NULL)
```

---

#### 🌐 Real-World Q&A:

**Q:** Can a table have multiple UNIQUE keys?  
**A:** Yes, unlike primary keys, a table can have multiple unique constraints.

**Q:** Can two rows have NULL in a UNIQUE column?  
**A:** Yes in most systems (e.g., PostgreSQL, MySQL), because NULL is considered “unknown”, not equal.

---

### 🔸 Nullability

#### ✅ Definition:

**Nullability** defines whether a column can have **NULL values**, i.e., absence of a value.

---

#### 📥 Syntax:

```sql
CREATE TABLE Products (
  ProductID INT PRIMARY KEY,
  Description TEXT,
  Discount INT NULL,
  LaunchDate DATE NOT NULL
);
```

- `Discount` → can be NULL (optional field)
- `LaunchDate` → NOT NULL (mandatory field)

---

#### ✅ Behavior:

- `NULL ≠ 0`
- `NULL ≠ ''` (empty string)
- `NULL ≠ NULL` (two unknowns are not equal)

---

#### 💡 NULL-Sensitive Queries:

```sql
SELECT * FROM Products WHERE Discount IS NULL;
```

```sql
-- ❌ This does not work:
SELECT * FROM Products WHERE Discount = NULL;
```

---

#### 🌐 Real-World Q&A:

**Q:** Why can't we compare with `= NULL`?  
**A:** Because `NULL` means unknown; instead, use `IS NULL` or `IS NOT NULL`.

**Q:** Can primary keys be nullable?  
**A:** No — primary keys must be **NOT NULL** by definition.

---

### 🔸 CHECK Constraints

#### ✅ Definition:

The `CHECK` constraint ensures that all values in a column **satisfy a specified logical condition**.

---

#### 📥 Example:

```sql
CREATE TABLE Students (
  RollNo INT PRIMARY KEY,
  Age INT CHECK (Age >= 18 AND Age <= 35),
  Grade CHAR(1) CHECK (Grade IN ('A', 'B', 'C', 'D', 'F'))
);
```

- Ensures only valid ages and grades are inserted.

---

#### 💡 Insertion Examples:

```sql
-- ✅ Valid:
INSERT INTO Students VALUES (101, 21, 'A');

-- ❌ Invalid Age:
INSERT INTO Students VALUES (102, 12, 'B');  -- Fails

-- ❌ Invalid Grade:
INSERT INTO Students VALUES (103, 25, 'Z');  -- Fails
```

---

#### 🌐 Real-World Q&A:

**Q:** Can CHECK be used on multiple columns?  
**A:** Yes — e.g., enforce logical conditions across columns:

```sql
CHECK (StartDate <= EndDate)
```

**Q:** Is CHECK constraint enforced in all databases?  
**A:** Not always. Some DBs (like older MySQL versions) parsed but did **not enforce** them.

---

## 🔷 8. Normalization

---

### 🔸 Functional Dependency (FD)

#### ✅ Definition:

A **Functional Dependency (FD)** `X → Y` exists in a relation if **for every value of X, there is exactly one corresponding value of Y**.

- It is a **constraint between two sets of attributes** in a relation.

---

#### 📥 Example:

```
Employee(EmpID, Name, DeptID, DeptName)

EmpID → Name        ✅ Each EmpID has a unique Name
DeptID → DeptName   ✅ Each department has a fixed name
```

---

#### 🔍 Diagram:

```
EmpID → Name
DeptID → DeptName
(EmpID, DeptID) → Salary
```

---

#### 🌐 Real-World Q&A:

**Q:** Why are FDs important?  
**A:** They help identify redundancy and anomalies in relational schemas and guide normalization.

---

### 🔸 Armstrong’s Axioms

#### ✅ Definition:

A **set of inference rules** to derive all valid FDs from a given set. These rules are:

1. **Reflexivity**: If Y ⊆ X, then X → Y
2. **Augmentation**: If X → Y, then XZ → YZ
3. **Transitivity**: If X → Y and Y → Z, then X → Z

---

#### ✅ Additional (Derived) Rules:

- **Union**: If X → Y and X → Z, then X → YZ
- **Decomposition**: If X → YZ, then X → Y and X → Z
- **Pseudotransitivity**: If X → Y and WY → Z, then WX → Z

---

#### 📥 Example:

Given:

- A → B
- B → C

Then by **Transitivity**: A → C

---

#### 🌐 Real-World Q&A:

**Q:** What are Armstrong’s Axioms used for?  
**A:** To derive **additional functional dependencies** logically and help compute closure and minimal covers.

---

### 🔸 Closure of FDs

#### ✅ Definition:

The **closure of a set of attributes X**, denoted as `X⁺`, is the **set of all attributes that are functionally determined by X**, given a set of FDs.

---

#### 📐 Step-by-step Example:

Given:

- R(A, B, C, D)
- F = { A → B, B → C, A → D }

Find `A⁺`:

```text
Start with A⁺ = {A}
Apply A → B → A⁺ = {A, B}
Apply B → C → A⁺ = {A, B, C}
Apply A → D → A⁺ = {A, B, C, D}
```

✅ A⁺ = {A, B, C, D}

---

#### 🌐 Real-World Q&A:

**Q:** Why compute closures?  
**A:** To check:

- If a key exists (does X⁺ = all attributes?)
- If a dependency is implied (X → Y ∈ F⁺?)
- For computing candidate keys and normalization

---

### 🔸 Minimal Cover

#### ✅ Definition:

A **minimal cover** (or canonical cover) of a set of FDs is a simplified set of FDs that:

1. Has a **single attribute** on the right-hand side (RHS)
2. Has **no extraneous attributes** on the left-hand side (LHS)
3. Contains **no redundant dependencies**

---

#### 📐 Step-by-Step Process:

Given:

```
F = { A → BC, B → C, A → B, AB → C }
```

1. **Split RHS**:

```
A → B
A → C
B → C
AB → C
```

2. **Remove redundant dependencies**:
   Check if any dependency can be derived from others using closures.

- AB → C is redundant because:
  - A → B
  - B → C
  - ⇒ A → C (transitive)
  - ⇒ AB → C not needed

Final minimal cover:

```
A → B
A → C
B → C
```

---

#### 🌐 Real-World Q&A:

**Q:** Why use minimal cover?  
**A:** To simplify the schema design and normalization steps. It eliminates redundant rules and improves performance.

**Q:** Is minimal cover unique?  
**A:** Not always. The exact minimal cover may vary **based on the order of simplification**, but it will always be **functionally equivalent**.

---

## 🔷 Types of Normal Forms

---

### 🔸 1NF – First Normal Form

#### ✅ Definition:

A relation is in **1NF** if:

- All attributes are **atomic** (no multi-valued or nested attributes)
- No repeating groups or arrays

---

#### ❌ Violation Example:

```text
Student(RollNo, Name, Courses)

101, Ayush, {DBMS, CN}
```

✅ Fix (flatten into atomic rows):

```text
RollNo | Name  | Course
-------------------------
101    | Ayush | DBMS
101    | Ayush | CN
```

---

#### 🌐 Real-World Q&A:

**Q:** Is 1NF mandatory in relational DBs?  
**A:** Yes. All relational tables must satisfy 1NF.

---

### 🔸 2NF – Second Normal Form

#### ✅ Definition:

A relation is in **2NF** if:

- It is in **1NF**
- **No partial dependency** (non-prime attribute dependent on part of a composite key)

---

#### ❌ Violation Example:

```text
Enrollment(StudentID, CourseID, StudentName)

Composite Key: (StudentID, CourseID)

Violation: StudentName depends only on StudentID
```

✅ Fix (Decompose):

```text
Student(StudentID, StudentName)
Enrollment(StudentID, CourseID)
```

---

### 🔸 3NF – Third Normal Form

#### ✅ Definition:

A relation is in **3NF** if:

- It is in **2NF**
- No **transitive dependency** (non-prime attribute depends on another non-prime)

---

#### ❌ Violation Example:

```text
Employee(EmpID, DeptID, DeptName)

EmpID → DeptID → DeptName
```

✅ Fix:

```text
Employee(EmpID, DeptID)
Department(DeptID, DeptName)
```

---

#### 🌐 Real-World Q&A:

**Q:** What's a transitive dependency?  
**A:** A → B and B → C implies A → C. If A is key and C is non-prime, that’s transitive.

---

### 🔸 BCNF – Boyce-Codd Normal Form

#### ✅ Definition:

A relation is in **BCNF** if:

- For every functional dependency `X → Y`, **X is a super key**

---

#### ❌ Violation Example:

```text
R(Course, Instructor, Room)
FDs:
  Course → Room
  Instructor → Room

Instructor is not a super key → violates BCNF
```

✅ Fix: Decompose into 2 BCNF relations.

---

#### 🌐 Real-World Q&A:

**Q:** Is every 3NF table also in BCNF?  
**A:** No. **All BCNF tables are 3NF**, but not vice versa.

---

### 🔸 4NF – Fourth Normal Form (Multivalued Dependency)

#### ✅ Definition:

A relation is in **4NF** if:

- It is in **BCNF**
- No **non-trivial multivalued dependencies**

---

#### 📥 Example:

```text
Student(Name, Hobby, Language)

Hobby and Language are independent → MVDs:
  Name →→ Hobby
  Name →→ Language
```

✅ Fix: Decompose:

```text
StudentHobbies(Name, Hobby)
StudentLanguages(Name, Language)
```

---

### 🔸 5NF – Fifth Normal Form (Join Dependency)

#### ✅ Definition:

A relation is in **5NF** if:

- It cannot be further decomposed without **losing data or meaning**
- Handles **join dependencies**

---

#### 📥 Example:

Consider a relation:

```
Project(Employee, Task, Tool)
```

Can be decomposed into 3 relations:

- (Employee, Task)
- (Task, Tool)
- (Employee, Tool)

If original table ≠ natural join of all 3, it violates 5NF.

---

### 🔸 6NF – Sixth Normal Form

#### ✅ Definition:

- Rarely used
- Each relation is **irreducible** (only attributes fully dependent on the key and **no non-trivial temporal dependencies**)

Used in **temporal databases**, data warehouses with **time-varying attributes**.

---

#### 🌐 Real-World Q&A:

**Q:** Do we normalize to 6NF in practice?  
**A:** No. Typically **up to 3NF or BCNF** is used. Higher NFs are rare in transactional systems.

**Q:** When is 4NF/5NF relevant?  
**A:** When dealing with **multivalued**, **multi-fact** data like surveys, catalogs, or configuration databases.

---

## 🔷 Denormalization

---

#### ✅ Definition:

**Denormalization** is the process of **introducing redundancy** by combining tables to **improve read performance**.

---

#### ✅ When to Denormalize:

- Too many joins reduce performance
- Reporting/analytics-heavy systems
- Read-heavy workloads

---

#### 📥 Example:

Normalized:

```text
Orders(OrderID, CustomerID)
Customers(CustomerID, Name)
```

Denormalized:

```text
Orders(OrderID, CustomerID, CustomerName)
```

---

#### 🌐 Real-World Q&A:

**Q:** Does denormalization mean poor design?  
**A:** No. In **OLAP and real-time dashboards**, it's often a **deliberate trade-off** for speed.

**Q:** What are the risks?  
**A:** Update anomalies, inconsistent data, storage overhead.

---

## 🔷 9. Indexing

---

### 🔸 Need for Indexing

#### ✅ Definition:

**Indexing** is a data structure technique used to **optimize the speed of data retrieval** from a database table without scanning the entire table.

---

#### ✅ Benefits:

- Speeds up **SELECT** queries and **WHERE** clause filters
- Reduces **disk I/O**
- Supports **ORDER BY**, **GROUP BY**, and **JOIN** operations

---

#### 📥 Without Index:

```sql
SELECT * FROM Employee WHERE EmpID = 105;
-- Full table scan required
```

✅ With Index → Fast direct access using a B-tree or hash map.

---

### 🔸 Types of Indexing

---

### 🔹 1. Single-Level Index

#### ✅ Definition:

An index with a **single level of pointers** to data blocks.

- Implemented as a **sorted list** with block addresses.

---

#### 📥 Example:

```
Index Table:
EmpID  | Block#
---------------
101    | B1
105    | B2
110    | B3
```

✅ Binary search can be used on index to locate block faster than linear scan.

---

### 🔹 2. Multi-Level Index

#### ✅ Definition:

A **hierarchical index** where the first-level index points to second-level index blocks, and so on — similar to a **B+ Tree**.

---

#### 🔍 Diagram:

```
Level 2 (Root Index)
      ↓
Level 1 (Index Blocks)
      ↓
Level 0 (Data Blocks)
```

✅ Great for **very large tables** where single-level index is too big.

---

### 🔹 3. Clustered vs Non-Clustered Index

---

#### ✅ Clustered Index:

- The data is **physically sorted** based on the indexed column.
- Only **one clustered index** per table.
- Index **modifies data storage order**.

```sql
CREATE CLUSTERED INDEX idx_empid ON Employee(EmpID);
```

---

#### ✅ Non-Clustered Index:

- **Separate structure** from data rows.
- Data is **not sorted** physically.
- Multiple non-clustered indexes allowed.

```sql
CREATE NONCLUSTERED INDEX idx_name ON Employee(Name);
```

---

#### 🔍 Visual:

```
Clustered Index:          Non-Clustered Index:
[Sorted Data Blocks]      [Index] → [Pointer to Data Blocks]
```

---

### 🔹 4. Primary Index vs Secondary Index

---

#### ✅ Primary Index:

- Defined on a **primary key** field
- Always **unique**
- Usually **clustered**

---

#### ✅ Secondary Index:

- Defined on a **non-primary key** field
- Can be **non-unique**
- Usually **non-clustered**

---

#### 📥 Example:

```sql
-- Primary Index (on EmpID)
CREATE INDEX idx_empid ON Employee(EmpID);

-- Secondary Index (on DeptID)
CREATE INDEX idx_deptid ON Employee(DeptID);
```

---

### 🔹 5. Dense vs Sparse Index

---

#### ✅ Dense Index:

- Every **record** in the data file has a corresponding entry in the index.

```text
Index: [101, 102, 103, 104, 105]
→ Points to every record
```

---

#### ✅ Sparse Index:

- Index entries exist for **only some records**.
- Typically, one index entry per **block/page**.

```text
Index: [101, 105, 110]
→ Points to data block start
```

✅ Takes **less space**, but may require more I/O during search.

---

#### 🌐 Real-World Q&A:

**Q:** Which is faster: clustered or non-clustered?  
**A:** Clustered is faster for range queries since rows are **physically sorted**.

**Q:** When to use sparse index?  
**A:** For large tables with **block-level** access and fewer lookups.

**Q:** Can a table have multiple indexes?  
**A:** Yes. One clustered index and multiple non-clustered indexes.

---

### 🔸 B+ Tree Indexing (Very Important)

#### ✅ Definition:

**B+ Tree** is a self-balanced tree structure used in databases for **dynamic multilevel indexing**.

- Used for **range queries** and **ordered traversal**
- All data entries are stored at the **leaf level**
- Internal nodes store only **keys**, not actual data

---

#### 🔍 Structure:

```
       [20 | 40 | 60]       ← Internal Node
       /   |    |   \
    [5 10] [25 30] [45 50] [65 70]   ← Leaf Nodes
```

- Fast search, insert, delete in **O(log n)** time
- Supports **sequential access** (leaves are linked)

---

#### 📥 Example:

```sql
CREATE INDEX idx_empid ON Employee(EmpID);
```

This will typically create a **B+ Tree index** on `EmpID`.

---

#### 🌐 Real-World Q&A:

**Q:** Why B+ tree over B-tree?  
**A:** B+ tree stores all actual records in leaves, allows for **efficient range queries** and **sorted scans**.

**Q:** Where are B+ Trees used?  
**A:** Almost all RDBMS systems (e.g., MySQL, PostgreSQL) use B+ Trees for indexing.

---

### 🔸 Hash Indexing

#### ✅ Definition:

A **hash index** uses a **hash function** to compute the location of a key — direct access, **constant time lookup**.

- Best for **equality-based searches**
- Not suitable for **range queries**

---

#### 📥 Example:

```sql
-- In PostgreSQL
CREATE INDEX idx_hash ON Employee(EmpID) USING HASH;
```

---

#### 🔍 Structure:

```
Key: 105 → Hash: h(105) = 3 → Bucket 3
```

---

#### 🌐 Real-World Q&A:

**Q:** Why not use hash indexes for range queries?  
**A:** Hash functions lose the **ordering**, so you can't find values between 100–200 without scanning all buckets.

**Q:** Where are hash indexes used?  
**A:** Ideal for caching, key-value lookups, and **NoSQL systems** like Redis.

---

### 🔸 Composite Indexing

#### ✅ Definition:

An index on **two or more columns**.

```sql
CREATE INDEX idx_emp_dept ON Employee(DeptID, Name);
```

- Useful for queries filtering on **prefix** of the columns.
- Only works if the query starts with **leftmost column(s)**.

---

#### 💡 Optimization Rule:

```text
WHERE DeptID = 1 AND Name = 'Ayush'  ✅ Uses index
WHERE Name = 'Ayush'                ❌ Index ignored
```

---

#### 🌐 Real-World Q&A:

**Q:** Can composite indexes replace multiple single-column indexes?  
**A:** Sometimes. They’re more effective when queries filter by the **same group of columns**.

---

### 🔸 Covering Index

#### ✅ Definition:

An index that **includes all columns needed** to satisfy a query — eliminates the need to access the table.

```sql
CREATE INDEX idx_cover ON Employee(EmpID, Name, Age);
```

If query is:

```sql
SELECT Name, Age FROM Employee WHERE EmpID = 101;
```

→ It’s fully satisfied from the index alone.

---

#### ✅ Benefits:

- No need to access the base table (fewer I/Os)
- Boosts read performance for selective queries

---

#### 🌐 Real-World Q&A:

**Q:** How to identify a covering index?  
**A:** If all **SELECT**, **WHERE**, and **JOIN** columns are in the index.

**Q:** When is this helpful?  
**A:** In read-heavy applications (e.g., dashboards, reports).

---

### 🔸 Bitmap Index (for OLAP)

#### ✅ Definition:

A **bitmap index** uses bit arrays (0s and 1s) for **each distinct value** of a column.

- Great for columns with **low cardinality** (few unique values)
- Efficient in **OLAP systems**, data warehouses

---

#### 📥 Example:

```text
Gender: M, F
Bitmaps:
M → 1 0 1 0 0
F → 0 1 0 1 1
```

- Row 1: Male
- Row 2: Female

---

#### ✅ Use Case:

```sql
SELECT COUNT(*) FROM Employee WHERE Gender = 'F';
```

→ Directly count 1s in the F bitmap → Fast!

---

#### 🌐 Real-World Q&A:

**Q:** Why not use bitmap index in OLTP?  
**A:** Because frequent updates make bitmap indexes **expensive to maintain**.

**Q:** What columns are ideal for bitmap indexes?  
**A:** Gender, Region, Status — **categorical with few values**.

---

## 🔷 10. Transactions and Concurrency Control

---

### 🔸 What is a Transaction?

#### ✅ Definition:

A **transaction** is a **sequence of one or more SQL operations** (such as insert, delete, update) that forms a **single logical unit of work**.

- Either **all operations succeed** (COMMIT)
- Or **none are applied** (ROLLBACK)

---

#### 📥 Example:

```sql
BEGIN;
UPDATE Accounts SET Balance = Balance - 1000 WHERE AccID = 101;
UPDATE Accounts SET Balance = Balance + 1000 WHERE AccID = 202;
COMMIT;
```

✅ If any step fails, you can `ROLLBACK` to undo all previous steps.

---

#### 🌐 Real-World Q&A:

**Q:** Why are transactions needed?  
**A:** To ensure **data consistency** in scenarios like bank transfers, ticket bookings, etc.

---

### 🔸 ACID Properties

ACID stands for the **four key properties** of a reliable database transaction.

---

#### ✅ A – Atomicity:

- A transaction is **all or nothing**
- If one step fails, the entire transaction fails

🧠 Think: **Undo all if anything fails**

---

#### ✅ C – Consistency:

- Ensures that the database moves from one **valid state to another**
- Enforces integrity constraints

🧠 Think: **No corruption or broken rules after transaction**

---

#### ✅ I – Isolation:

- Transactions do not interfere with each other
- Intermediate states are **invisible** to other transactions

🧠 Think: **Act as if only one transaction is running at a time**

---

#### ✅ D – Durability:

- Once committed, changes are **permanently saved** even if the system crashes

🧠 Think: **Changes survive power failures and crashes**

---

#### 📥 Example:

```sql
-- Without Isolation:
T1: SELECT Balance FROM A;
T2: UPDATE Balance of A;

T1 might read uncommitted dirty value → violates Isolation
```

---

#### 🌐 Real-World Q&A:

**Q:** Which property is violated in power failure after COMMIT but before write to disk?  
**A:** **Durability**

**Q:** Can a transaction be consistent but not durable?  
**A:** Yes, if changes are not persisted after a crash.

---

### 🔸 Transaction States

#### ✅ Diagram:

```
[Active]
   ↓ (all ops done)
[Partially Committed]
   ↓ COMMIT
[Committed]
   ↓
[Terminated]

   ↓ Error
[Failed]
   ↓
[Aborted]
```

---

#### ✅ State Descriptions:

| State                   | Description                                        |
| ----------------------- | -------------------------------------------------- |
| **Active**              | Transaction is being executed                      |
| **Partially Committed** | Last operation executed; commit not yet done       |
| **Committed**           | All changes made permanent                         |
| **Failed**              | Some error occurred during execution               |
| **Aborted**             | Transaction rolled back                            |
| **Terminated**          | Transaction finished (either committed or aborted) |

---

#### 📥 Example Walkthrough:

```sql
BEGIN;
-- Active
UPDATE Balance ...
-- Partially Committed
COMMIT;
-- Committed
```

---

#### 🌐 Real-World Q&A:

**Q:** Can a transaction go from Committed to Aborted?  
**A:** No. Once committed, it **cannot be rolled back**.

**Q:** Can rollback be done manually before commit?  
**A:** Yes. You can issue `ROLLBACK;` during Active/Partially Committed state.

---

## 🔷 Serializability & Concurrency Anomalies

---

### 🔸 Serializability

#### ✅ Definition:

**Serializability** ensures the **concurrent execution** of transactions results in a **state equivalent to some serial execution** (i.e., one after another).

---

### 🔹 Conflict Serializability

#### ✅ Definition:

A schedule is **conflict-serializable** if it can be transformed into a **serial schedule** by **swapping non-conflicting operations**.

---

#### ✅ Conflicting Operations:

Two operations conflict if:

- They access the **same data item**
- At least one of them is a **write**

---

#### 🔍 Example:

```text
T1: R(X)   W(X)
T2:     R(X)   W(X)

Schedule:
T1: R(X) ---- W(X)
T2:      R(X) ---- W(X)

→ Conflicting operations: W(X) by T1 and W(X) by T2
```

Build a **precedence graph**:

- If **acyclic**, then schedule is **conflict-serializable**

---

### 🔹 View Serializability

#### ✅ Definition:

A schedule is **view-serializable** if it results in the **same final read/write behavior** as a serial schedule, regardless of operation order.

- Less restrictive than conflict serializability
- Harder to test (NP-Complete)

---

#### 🔍 View Equivalence Conditions:

- Same transactions read initial value
- Same transactions read from same transactions
- Same final writes

---

#### 🌐 Real-World Q&A:

**Q:** Which is stricter: conflict or view serializability?  
**A:** **Conflict serializability** ⊂ **View serializability**

**Q:** Why prefer conflict-serializable schedules?  
**A:** Easier to detect and enforce via **lock-based protocols**.

---

### 🔸 Concurrency Anomalies

---

### 🔹 Dirty Read

#### ✅ Definition:

A transaction reads **uncommitted changes** made by another transaction.

---

#### 🔁 Scenario:

```text
T1: UPDATE balance = 500
T2: SELECT balance = 500   ← Dirty Read
T1: ROLLBACK
```

✅ T2 read a **rolled-back value** → Inconsistent

---

### 🔹 Non-repeatable Read

#### ✅ Definition:

A transaction reads **same row twice** and gets **different values**, due to another transaction's update in between.

---

#### 🔁 Scenario:

```text
T1: SELECT salary FROM Emp WHERE id = 101 → 50K
T2: UPDATE Emp SET salary = 70K WHERE id = 101
T1: SELECT salary FROM Emp WHERE id = 101 → 70K
```

✅ T1 sees **non-repeatable** values

---

### 🔹 Phantom Read

#### ✅ Definition:

A transaction re-executes a **range query** and sees **new rows** inserted by another transaction.

---

#### 🔁 Scenario:

```text
T1: SELECT * FROM Orders WHERE price > 500  → 2 rows
T2: INSERT INTO Orders(price) VALUES (1000)
T1: SELECT * FROM Orders WHERE price > 500  → 3 rows
```

✅ Phantom row appears

---

#### 🔍 Summary Table:

| Anomaly                 | Cause                           | Example Effect                    |
| ----------------------- | ------------------------------- | --------------------------------- |
| **Dirty Read**          | Read uncommitted changes        | Read a value that was rolled back |
| **Non-repeatable Read** | Re-read returns different data  | Update during transaction         |
| **Phantom Read**        | Insert/delete during range scan | Extra/missing rows in re-scan     |

---

#### 🌐 Real-World Q&A:

**Q:** How to prevent dirty reads?  
**A:** Use **Read Committed** or higher isolation levels.

**Q:** Which isolation level prevents phantom reads?  
**A:** Only **Serializable** isolation level guarantees that.

**Q:** Are these anomalies acceptable in some systems?  
**A:** Yes — in high-throughput systems (e.g., OLAP), weaker isolation is acceptable for performance.

---

## 🔷 Concurrency Control & Deadlocks

---

### 🔸 Concurrency Control Protocols

---

### 🔹 Lock-Based Protocols

#### ✅ Shared Lock (S):

- Allows **read** access
- Multiple transactions can **share the same data**

#### ✅ Exclusive Lock (X):

- Allows **read & write**
- Only **one transaction** can hold it

---

#### 🔁 Example:

| T1           | T2           |
| ------------ | ------------ | -------------------------- |
| S-Lock(A)    |              |
| Read A       |              |
|              | S-Lock(A) ✅ |
|              | Read A       |
| X-Lock(A) ❌ |              | ← Waits due to shared lock |

---

#### 🌐 Real-World Q&A:

**Q:** What happens if X-lock is requested while S-locks exist?  
**A:** Must wait until all S-locks are released.

---

### 🔹 Two-Phase Locking (2PL)

#### ✅ Definition:

A transaction must follow two phases:

1. **Growing Phase**: Can acquire locks but **cannot release**
2. **Shrinking Phase**: Can release locks but **cannot acquire**

✅ Guarantees **conflict-serializability**

---

#### 🔁 Timeline:

```
|---- Growing ----|---- Shrinking ----|
Acquire → Acquire → Release → Release
```

---

### 🔹 Strict 2PL

#### ✅ Special case of 2PL:

- All **exclusive locks are held till COMMIT/ROLLBACK**
- Prevents **dirty reads**, enables **recoverability**

---

### 🔹 Timestamp-Based Protocols

#### ✅ Each transaction gets:

- **TS(Ti)** = timestamp when transaction Ti starts

For every data item `Q`, maintain:

- `read_TS(Q)`: latest read timestamp
- `write_TS(Q)`: latest write timestamp

---

#### 🔁 Rules:

- If Ti wants to **read Q**, check if `TS(Ti) ≥ write_TS(Q)`
- If Ti wants to **write Q**, ensure:
  - `TS(Ti) ≥ read_TS(Q)` AND `TS(Ti) ≥ write_TS(Q)`
  - Otherwise → **rollback Ti**

✅ Ensures **serializability based on timestamps**

---

### 🔹 Validation-Based Protocols (Optimistic Concurrency)

#### ✅ Phases:

1. **Read Phase**: Read values into local variables
2. **Validation Phase**: Validate transaction can be serialized
3. **Write Phase**: Apply updates if validation succeeds

✅ Best for **low-conflict environments** (e.g., OLAP)

---

#### 🌐 Real-World Q&A:

**Q:** Which protocol is used in MySQL/InnoDB?  
**A:** Uses a mix of **locking** and **MVCC** (multi-version concurrency control)

---

### 🔸 Deadlock

---

### 🔹 Deadlock Definition

Occurs when:

- Two or more transactions are **waiting for each other** to release locks
- Cycle of waiting → **circular wait**

---

### 🔹 Deadlock Detection

- Maintain a **Wait-for Graph**
  - Nodes = Transactions
  - Edge T1 → T2 if T1 is waiting for a resource held by T2

✅ If the graph has a **cycle**, deadlock exists

---

#### 🔍 Example Wait-for Graph:

```
T1 → T2 → T3 → T1 ← Cycle → Deadlock
```

---

### 🔹 Deadlock Prevention

- Use **timestamp ordering**:
  - **Wait-Die**: Older waits, younger dies
  - **Wound-Wait**: Older preempts, younger waits

---

### 🔹 Deadlock Avoidance

- Use **Banker’s Algorithm**-like method
- Allow lock if system remains in **safe state**

Rare in practice due to **overhead**

---

#### 🌐 Real-World Q&A:

**Q:** Which is more used — detection or prevention?  
**A:** Detection + timeout is preferred in real DBMSs (cheaper than constant prevention).

---

### 🔸 Starvation

#### ✅ Definition:

A transaction is **continuously denied access** to a resource due to other higher-priority transactions.

---

#### 🔁 Scenario:

- T1 repeatedly requests lock
- T2, T3 always preempt it
- T1 **never progresses**

---

#### ✅ Solution:

- **Fair locking**
- **Aging mechanism**: Increase priority of long-waiting transactions

---

#### 🌐 Real-World Q&A:

**Q:** Is starvation same as deadlock?  
**A:** No. Starvation is due to **indefinite delay**, not circular wait.

**Q:** How do databases handle starvation?  
**A:** By using **first-come-first-serve queues** or **aging**.

---

## 🔷 11. Recovery and Logging

---

### 🔸 Failure Types

#### ✅ Types of Failures in DBMS:

| Failure Type            | Description                                |
| ----------------------- | ------------------------------------------ |
| **Transaction Failure** | Logical error or user abort                |
| **System Crash**        | Hardware/software crash (e.g., power loss) |
| **Media Failure**       | Disk crash or storage failure              |
| **Application Error**   | Bugs, improper input                       |

---

### 🔸 Recovery Techniques

---

### 🔹 Log-Based Recovery

#### ✅ Concept:

- Maintain a **log file** recording all **DB modifications**
- Used to **redo** committed transactions or **undo** uncommitted ones

---

#### 🔍 Log Format:

```text
<START T1>
<T1, A, old_value, new_value>
<COMMIT T1>
```

- Stored on stable storage (non-volatile)
- **Sequential writes** for efficiency

---

### 🔹 Deferred Update

#### ✅ Principle:

- All updates are **buffered in memory**
- Changes are applied to DB **only after COMMIT**
- Safe to ignore UNDO (no DB changes before commit)

---

#### 🔁 Example:

```text
<START T1>
<T1, A, 10 → 50>
<COMMIT T1> → Apply 50 to A
```

---

### 🔹 Immediate Update

#### ✅ Principle:

- DB is **updated during transaction**
- Logs are written **before updates**
- Requires **UNDO + REDO** during recovery

---

#### 🔁 Example:

```text
<START T1>
<T1, A, 10 → 50> → Apply immediately
<COMMIT T1>
```

If crash occurs:

- T1 committed → **REDO**
- T1 not committed → **UNDO**

---

### 🔸 Write-Ahead Logging (WAL)

#### ✅ Rule:

Before making any change to the database:

- **The log must be written to disk first**

✅ Ensures:

- Recovery is possible using logs
- Follows **Durability (D in ACID)**

---

#### 🔍 Order:

```text
1. Write <T1, A, old, new> to log
2. Flush log to disk
3. Write new value to DB
```

---

### 🔸 ARIES Protocol

#### ✅ Stands for:

**A**lgorithm for **R**ecovery and **I**solation **E**xploiting **S**emantics

Widely used in DBMSs like **IBM DB2** and **SQL Server**

---

### 🔹 ARIES Phases:

#### 1. **Analysis Phase**:

- Scan log to find **dirty pages**, **active transactions**
- Build **Transaction Table** and **Dirty Page Table**

---

#### 2. **Redo Phase**:

- Reapply all changes from log starting at the earliest **LSN** (Log Sequence Number) in Dirty Page Table
- Ensures committed changes are not lost

---

#### 3. **Undo Phase**:

- Rollback uncommitted transactions by **undoing log entries in reverse order**
- Log each undo with **Compensation Log Record (CLR)**

---

#### 🔍 Diagram Overview:

```
+------------+       +-----------+       +----------+
|  Analysis  |  →→→  |   Redo    |  →→→  |   Undo   |
+------------+       +-----------+       +----------+
        ↓                  ↓                  ↓
 Transaction Tbl       Apply Logs        Rollback Uncommitted
 Dirty Page Tbl        From Checkpoint   Using CLRs
```

---

### 🌐 Real-World Q&A

**Q:** Why WAL is essential in recovery?  
**A:** Ensures that recovery can **redo/undo operations** using logs even if system crashes.

**Q:** When is Deferred Update used?  
**A:** In simpler systems or when **performance trade-offs** are acceptable.

**Q:** What makes ARIES powerful?  
**A:** It supports:

- Fine-grained recovery
- Concurrent transactions
- Recovery from any point using checkpoints

---

### 🔸 Checkpoints

#### ✅ Definition:

A **checkpoint** is a snapshot of the current database state, taken to **reduce recovery time** in case of a failure.

---

#### 🔍 Why Use Checkpoints?

- Without checkpoints, recovery must scan **entire log**
- With checkpoints, recovery can start **after last checkpoint**

---

#### 📥 Example Log:

```text
<Checkpoint>
<START T3>
<T3, A, 100 → 200>
<COMMIT T3>
```

If a crash occurs, recovery can **ignore logs before checkpoint** safely.

---

#### ✅ Checkpointing Process:

1. Flush all dirty buffers to disk
2. Write a checkpoint record in log
3. Flush log to disk

---

### 🔸 Shadow Paging

#### ✅ Definition:

A **non-log-based** recovery mechanism using **two page tables**:

- **Current Page Table**
- **Shadow Page Table** (readonly, points to stable version)

---

#### 🔍 Process:

1. On transaction start, copy current page table to shadow
2. Perform updates using **new pages**
3. On commit, overwrite the current page table

✅ Old pages remain unchanged → recovery is **instantaneous**

---

#### 📥 Example:

```text
• Page Table (before) → P1, P2, P3
• Update → P3'
• Commit → Switch pointer from P3 → P3'
```

---

#### 🔴 Limitations:

- No support for **concurrency**
- Inefficient for frequent updates
- Modern DBMS prefer **WAL + ARIES**

---

### 🔸 Cascading Aborts

#### ✅ Definition:

Occurs when one transaction abort causes **other dependent transactions** to also abort.

---

#### 🔁 Scenario:

```text
T1: Writes X
T2: Reads X
T1: Aborts → T2 must also abort
```

---

#### 🔍 Diagram:

```
T1 → writes X
T2 → reads X ← dependency
T1 aborts ⇒ T2 aborts ⇒ cascading effect
```

---

#### ✅ Prevention:

Use **Strict 2PL** → Delay reads/writes until previous transactions **commit**

---

### 🔸 Idempotency in Recovery

#### ✅ Definition:

An operation is **idempotent** if executing it **multiple times** has **no side effects beyond the initial application**.

---

#### ✅ In Recovery:

- **Redo** operations may be repeated
- Must not corrupt data if log replay happens twice

---

#### 📥 Example:

```sql
UPDATE balance = 1000
-- Reapplied → Still 1000
```

✅ Safe if operations are **idempotent**

---

#### 🔍 Importance:

- Ensures **log replay** is reliable
- Used heavily in **ARIES Redo Phase**

---

## 🔷 12. File Organization & Storage

---

### 🔸 File Types

---

### 🔹 Heap File

#### ✅ Definition:

- Records are stored **in no particular order**
- New records go to **first available space**

✅ Simple and efficient for **inserts**

---

### 🔹 Sorted File

#### ✅ Definition:

- Records stored **in sorted order** based on one or more fields
- Enables **binary search**

✅ Efficient for **range queries**

---

### 🔹 Hashed File

#### ✅ Definition:

- A **hash function** determines the page/block for a record
- Supports **equality-based searches**

---

#### 📥 Example:

```text
Hash(Key) → Block Number
```

---

### 🔸 Pages, Blocks, Records

#### ✅ Page:

- Smallest unit of **data transferred between disk and memory**

#### ✅ Block:

- A group of **pages** or physical unit read/write from disk

#### ✅ Record:

- One tuple or row in a relation

---

#### 🔍 Diagram:

```
Disk
└── Block 1
    ├── Page 1
    │   ├── Record A
    │   └── Record B
```

---

### 🔸 Slotted Page Structure

#### ✅ Structure used to manage variable-sized records in a page

#### 🔍 Layout:

```
+-----------------------------+
| Free Space Offset          |
| Number of Records (n)      |
| Slot Directory (n entries) |
| Record n                   |
| Record n-1                 |
| ...                        |
| Record 1                   |
+-----------------------------+
```

✅ Supports insert, delete, and update efficiently

---

### 🔸 Fixed-Length vs Variable-Length Records

---

#### ✅ Fixed-Length:

- Each field has **fixed size**
- Simple to store and access
- Fast but space may be **wasted**

---

#### ✅ Variable-Length:

- Fields can have **variable size**
- More compact but **access is slower**
- Needs **offsets or delimiters**

---

### 🔸 Buffer Management

#### ✅ Definition:

Manages memory buffers (RAM) for **temporary storage** of disk pages

---

#### ✅ Functions:

- Load pages from disk
- Manage dirty/clean status
- Evict pages using policies (e.g., **LRU, MRU**)

---

#### 🔍 Buffer Pool Diagram:

```
[Buffer Frame 1] ← Page A
[Buffer Frame 2] ← Page B (dirty)
[Buffer Frame 3] ← Empty
```

✅ Dirty pages written back to disk on eviction

---

### 🔸 Block Access and Cost Models

#### ✅ Cost Model:

Estimates cost of disk operations in terms of **block transfers**

---

#### 📥 Example Costs:

- **Sequential Access** → 1 I/O per block
- **Random Access** → Higher due to **seek time + latency**

---

#### 🔍 Formula:

```
Total Cost = (# of block accesses) × (I/O cost per block)
```

---

#### ✅ Use Cases:

- Query optimization
- Index design decisions

---

## 🔷 13. Query Processing & Optimization

---

### 🔸 Query Parsing and Translation

#### ✅ Parsing:

- SQL query is checked for **syntax and semantics**
- Generates a **parse tree**

#### ✅ Translation:

- Convert SQL into **relational algebra (RA) expressions**
- Intermediate form for optimization

---

#### 📥 Example:

```sql
SELECT Name FROM Employee WHERE Salary > 50000;
```

→ Translates to:

```
π_Name (σ_Salary>50000 (Employee))
```

---

### 🔸 Query Execution Plan (QEP)

#### ✅ Definition:

A **detailed blueprint** of how the database will execute the query

- Includes access methods, join order, index usage
- Can be **logical** or **physical**

---

#### 🔍 QEP Example:

```
Seq Scan on Employee
→ Filter: Salary > 50000
→ Output: Name
```

---

#### 📥 SQL Example (PostgreSQL):

```sql
EXPLAIN ANALYZE SELECT Name FROM Employee WHERE Salary > 50000;
```

→ Returns the QEP with actual execution cost

---

### 🔸 Cost Estimation

#### ✅ Purpose:

Estimate **I/O, CPU, and memory cost** of executing a query plan

---

#### ✅ Metrics:

- **Number of disk accesses**
- **Size of intermediate results**
- **Selectivity** of predicates

---

#### 📥 Example:

```text
Selectivity = (# of qualifying tuples) / (total tuples)
```

→ Used to estimate output size after filters

---

### 🔸 Heuristics for Query Optimization

#### ✅ Heuristic Rules:

1. Perform **selection early**
2. Perform **projection early** to reduce columns
3. Combine **selections and projections** if possible
4. Choose the most **selective joins first**
5. Use **index scans** where possible

---

#### 🔍 Example:

```sql
SELECT Name FROM Employee, Department
WHERE Employee.DeptID = Department.ID AND Salary > 50000;
```

→ Apply filter Salary > 50000 **before join** for efficiency

---

### 🔸 Join Order Optimization

#### ✅ Definition:

Reordering joins to minimize intermediate result sizes and total cost

---

#### 📥 Strategies:

- **Left-deep trees** → Join from left to right
- **Greedy algorithms** → Select cheapest pair at each step
- **Dynamic programming** → Optimal join order (expensive for many tables)

---

#### 🔍 Diagram:

```
( (A ⋈ B) ⋈ C ) vs ( A ⋈ (B ⋈ C) )
```

→ Optimal order depends on data size and join selectivity

---

#### 🌐 Real-World Q&A:

**Q:** Why not always use optimal plan?  
**A:** Finding the best plan is **NP-Hard** — approximations (heuristics) are used.

**Q:** What tool shows QEP in PostgreSQL?  
**A:** `EXPLAIN` or `EXPLAIN ANALYZE`

**Q:** Can the DB choose a bad plan?  
**A:** Yes — due to inaccurate **statistics** or outdated **cost estimations**

---

### 🔸 Materialized Views

#### ✅ Definition:

A **materialized view** stores the **result of a query physically** on disk, unlike a normal (virtual) view.

- Can be **periodically refreshed**
- Used for **performance** on expensive queries

---

#### 📥 Example:

```sql
CREATE MATERIALIZED VIEW TopSalaries AS
SELECT Name, Salary FROM Employee
WHERE Salary > 100000;
```

- Stored as an actual table
- Can be **refreshed manually or automatically**

```sql
REFRESH MATERIALIZED VIEW TopSalaries;
```

---

#### 🔍 Diagram:

```
Query  →  Result Table (stored)  →  Faster Re-use
```

---

#### 🌐 Real-World Q&A:

**Q:** Difference between normal view and materialized view?  
**A:** Normal view: re-executes each time; materialized view: stores result.

**Q:** Use case?  
**A:** Dashboards, analytics, reporting queries.

---

### 🔸 Query Caching

#### ✅ Definition:

Stores **previous query results** in memory to **serve repeated queries faster**.

- Avoids re-computation
- DBMS or external layer can manage the cache

---

#### 📥 Example:

```sql
SELECT COUNT(*) FROM Sales WHERE Region = 'West';
-- Cached after first run
```

✅ Next identical query is served **from cache**

---

#### ✅ Cache Invalidation:

- Automatic on **data update**
- Can be time-based or event-based

---

#### 🌐 Real-World Q&A:

**Q:** What’s the risk of query caching?  
**A:** **Stale data** if not invalidated correctly.

**Q:** Can query cache be customized?  
**A:** Yes — some systems allow manual cache hints or directives.

---

### 🔸 Pipelining vs Materialization

---

#### ✅ Pipelining:

- Intermediate results are **passed immediately** to next operation
- Saves memory and disk I/O
- Used in **iterators or generators**

---

#### ✅ Materialization:

- Intermediate results are **stored on disk or in memory**
- Useful for **reusing intermediate data**
- Adds overhead in terms of **I/O and space**

---

#### 🔍 Comparison Table:

| Feature        | Pipelining             | Materialization             |
| -------------- | ---------------------- | --------------------------- |
| Storage        | No (in-memory streams) | Yes (disk/memory)           |
| Speed          | Faster (low overhead)  | Slower (due to writes)      |
| Use case       | Lightweight queries    | Repeated intermediate usage |
| Fault recovery | Not possible           | Easier to recover           |

---

#### 📥 Example:

```sql
-- Materialization
SELECT * FROM (SELECT * FROM Orders WHERE Amount > 100) AS Temp;

-- Pipelining (streamed directly)
SELECT COUNT(*) FROM Orders WHERE Amount > 100;
```

---

#### 🌐 Real-World Q&A:

**Q:** Which is used in PostgreSQL by default?  
**A:** **Pipelining**, unless intermediate results are too large or reused.

**Q:** When is materialization better?  
**A:** When same intermediate result is needed multiple times (e.g., nested subqueries).

---

## 🔷 14. Distributed Databases

---

### 🔸 Characteristics & Advantages

#### ✅ What is a Distributed Database?

A **distributed database** is a collection of logically interrelated databases **distributed across multiple physical locations** and connected via a network.

---

#### ✅ Key Characteristics:

- **Location transparency**: Users don't know where data is stored
- **Replication transparency**: Data can be duplicated across sites
- **Fragmentation transparency**: Data can be split across nodes
- **Concurrency & Fault tolerance**: Handles concurrent users and failures
- **Autonomy**: Each site may be partially independent

---

#### ✅ Advantages:

- Improved **availability**
- Faster **local access**
- **Scalability**
- **Fault tolerance** due to replication
- **Modular growth**

---

### 🔸 Fragmentation

---

#### 🔹 Horizontal Fragmentation

#### ✅ Definition:

Table is **partitioned by rows** across multiple sites.

---

#### 📥 Example:

```text
Employee(India) = SELECT * FROM Employee WHERE Location = 'India';
Employee(US)    = SELECT * FROM Employee WHERE Location = 'US';
```

---

#### ✅ Use Case:

Queries on region-specific data (e.g., by geography)

---

#### 🔍 Diagram:

```
Employee Table
↓
[India Fragment] | [US Fragment] | [EU Fragment]
```

---

#### 🔹 Vertical Fragmentation

#### ✅ Definition:

Table is **partitioned by columns** and distributed.

---

#### 📥 Example:

```text
Emp1 = (EmpID, Name, Address)
Emp2 = (EmpID, Salary, Department)
```

Linked via **primary key (EmpID)**

---

#### ✅ Use Case:

When different sites query different attributes

---

#### 🔍 Diagram:

```
Employee Table
↓
[Basic Info]       [Work Info]
(EmpID, Name)   +  (EmpID, Salary)
```

---

### 🔸 Replication

#### ✅ Definition:

Same data is **copied across multiple sites**

---

#### ✅ Types:

- **Full Replication**: All data copied to every site
- **Partial Replication**: Only a subset of data is replicated
- **Synchronous Replication**: All replicas updated simultaneously
- **Asynchronous Replication**: Updates propagate with a delay

---

#### 📥 Example:

```text
Site A: Orders
Site B: Orders (replica)

→ Site B can serve reads if Site A is down
```

---

#### ✅ Pros:

- Improved **availability** and **read performance**
- **Fault tolerance** in case of site failure

---

#### ✅ Cons:

- Update **overhead**
- Risk of **inconsistency** in asynchronous replication

---

#### 🌐 Real-World Q&A:

**Q:** Why fragment data?  
**A:** To improve **query performance** and reduce **data transfer** across sites.

**Q:** Which is more suitable for analytics: replication or fragmentation?  
**A:** **Replication** for faster reads, **fragmentation** for distributed compute.

**Q:** How is consistency maintained in replicated databases?  
**A:** Via protocols like **2PC**, **quorum-based writes**, or **eventual consistency** models.

---

### 🔸 CAP Theorem

#### ✅ Definition:

**CAP Theorem** states that a distributed database can only guarantee **two out of three** properties at a time:

1. **Consistency (C)** – All nodes see the same data at the same time
2. **Availability (A)** – Every request gets a response (even if not up-to-date)
3. **Partition Tolerance (P)** – System continues functioning even if network partitions occur

---

#### 🔍 Diagram:

```
     [Consistency]
        /       \
    [A]         [P]
     \         /
      [Availability]
```

✅ In practice, **partition tolerance** is a must, so systems must choose between:

- **CP** (e.g., MongoDB with strong consistency)
- **AP** (e.g., Cassandra, DynamoDB)

---

#### 🌐 Real-World Q&A:

**Q:** Can a distributed system be CAP-complete?  
**A:** No — it can only provide **2 out of 3** during partitions.

---

### 🔸 BASE vs ACID

---

#### ✅ ACID (Traditional DBs):

- **Atomicity** – All or nothing
- **Consistency** – DB remains valid after transaction
- **Isolation** – Transactions don’t interfere
- **Durability** – Once committed, changes persist

---

#### ✅ BASE (NoSQL/Distributed Systems):

- **Basically Available** – Always responds
- **Soft state** – Data can change over time
- **Eventual consistency** – Data becomes consistent eventually

---

#### 🔍 Comparison:

| Feature      | ACID (SQL)         | BASE (NoSQL)               |
| ------------ | ------------------ | -------------------------- |
| Use Case     | Transactions, OLTP | Distributed, scalable apps |
| Consistency  | Strong             | Eventual                   |
| Availability | Secondary concern  | Prioritized                |

---

### 🔸 Two-Phase Commit (2PC)

#### ✅ Definition:

A protocol to ensure **atomic commitment** in distributed transactions.

---

#### 📥 Phases:

1. **Prepare Phase**:

   - Coordinator asks participants to **prepare to commit**
   - Each participant replies: _Yes (vote-commit)_ or _No (abort)_

2. **Commit Phase**:
   - If all vote yes → Send COMMIT
   - Else → Send ABORT

---

#### 🔍 Diagram:

```
Coordinator → [Prepare?] → Participants
← Vote (Yes/No)
↓
Commit / Abort
```

---

#### 🔴 Limitation:

- Blocking protocol → participants **wait indefinitely** if coordinator crashes

---

### 🔸 Three-Phase Commit (3PC)

#### ✅ Improvement over 2PC:

- Adds an **extra phase** to avoid blocking
- Uses **timeout and pre-commit** phase

---

#### 📥 Phases:

1. **CanCommit?**
2. **PreCommit**
3. **Commit**

✅ Ensures no participant is in doubt forever

---

#### ✅ Trade-off:

More network messages → Higher overhead

---

### 🔸 Eventual Consistency

#### ✅ Definition:

In **distributed systems**, all replicas will **converge to the same state** if no new updates are made.

---

#### 📥 Example:

- Amazon Dynamo, Cassandra, Riak

---

#### ✅ Use Case:

- Shopping carts, social feeds — temporary inconsistency acceptable

---

#### 🔍 Consistency Spectrum:

```
Strong → Bounded Staleness → Monotonic Reads → Eventual Consistency
```

---

#### 🌐 Real-World Q&A:

**Q:** Does eventual consistency guarantee correctness?  
**A:** Only **in the long run** — short-term reads may be stale.

---

### 🔸 Sharding and Partitioning

---

#### ✅ Sharding:

Horizontal partitioning of data across **different servers/nodes**.

---

#### 📥 Example:

```text
User IDs 1–1000 → Server A
User IDs 1001–2000 → Server B
```

---

#### ✅ Partitioning:

Generic term that includes:

- **Horizontal partitioning (sharding)**
- **Vertical partitioning** (splitting columns)
- **Functional partitioning** (by entity type)

---

#### 🔍 Diagram:

```
[Users Table]
↓
Shard 1 → Server A
Shard 2 → Server B
Shard 3 → Server C
```

---

#### 🌐 Real-World Q&A:

**Q:** Why shard?  
**A:** To handle large-scale data, reduce contention, and scale horizontally.

**Q:** What challenges arise from sharding?  
**A:** Cross-shard joins, rebalancing, hotspot management, and consistency.

---

## 🔷 15. NoSQL Databases

---

### 🔸 Characteristics of NoSQL

#### ✅ Definition:

**NoSQL** databases are non-relational, schema-less databases designed for:

- High scalability
- Flexible data models
- Distributed architectures

---

#### ✅ Key Features:

- Schema-less (flexible structure)
- Horizontally scalable
- High availability
- BASE properties (instead of ACID)
- Designed for distributed and Big Data applications

---

### 🔸 Types of NoSQL Databases

---

#### 🔹 Key-Value Stores

#### ✅ Example: Redis, Amazon DynamoDB

- Data is stored as **(key, value)** pairs
- Fast **lookups** using keys
- Values can be string, JSON, binary, etc.

---

#### 📥 Example:

```text
"username:1234" → "ayush_yadav"
```

---

✅ Use Case: Caching, session storage, simple user profiles

---

#### 🔹 Document Stores

#### ✅ Example: MongoDB, Couchbase

- Stores semi-structured data as **documents** (usually JSON/BSON)
- Supports nested objects and arrays
- Enables indexing, querying on document fields

---

#### 📥 Example:

```json
{
  "_id": "u123",
  "name": "Ayush",
  "skills": ["C++", "Verilog"],
  "address": {
    "city": "Bangalore",
    "zip": "560001"
  }
}
```

---

✅ Use Case: Content management, catalogs, user profiles

---

#### 🔹 Column-Family Stores

#### ✅ Example: Apache Cassandra, HBase

- Stores data in **rows and columns**, grouped into **column families**
- Suitable for sparse datasets and wide tables
- Optimized for **write-heavy** workloads

---

#### 📥 Example:

```
RowKey: user123
→ Name: Ayush
→ Age: 25
→ Location: Bangalore
```

---

✅ Use Case: Time-series data, logging systems, messaging

---

#### 🔹 Graph Databases

#### ✅ Example: Neo4j, ArangoDB

- Stores data as **nodes and edges**
- Designed for relationship-centric queries
- Supports graph traversal and shortest path

---

#### 📥 Example:

```
(Ayush) -[FRIENDS_WITH]-> (Rahul)
```

---

✅ Use Case: Social networks, recommendation engines, fraud detection

---

### 🔸 When to Use NoSQL

---

#### ✅ Situations:

- Need for **scalability** over consistency
- **Unstructured or semi-structured** data
- Rapidly changing schema
- High **write throughput**
- **Eventual consistency** acceptable

---

#### 🌐 Real-World Use Cases:

- Real-time analytics (e.g., log collection)
- IoT data ingestion
- E-commerce product catalogs
- User activity feeds

---

### 🔸 Differences from RDBMS

| Feature        | RDBMS               | NoSQL                      |
| -------------- | ------------------- | -------------------------- |
| Data Model     | Relational (tables) | Key-Value, Document, etc.  |
| Schema         | Fixed               | Dynamic / Schema-less      |
| Query Language | SQL                 | Varies (e.g., Mongo Query) |
| Consistency    | Strong (ACID)       | Eventual (BASE)            |
| Scalability    | Vertical (scale-up) | Horizontal (scale-out)     |
| Joins          | Supported           | Limited/Not supported      |
| Transactions   | Strong              | Weak or eventual           |

---

#### 🌐 Real-World Q&A:

**Q:** Why does NoSQL avoid joins?  
**A:** Joins are expensive in distributed systems; NoSQL prefers **denormalized data**.

**Q:** Can NoSQL databases be ACID compliant?  
**A:** Some (like MongoDB with transactions) offer **partial ACID** support.

**Q:** Should we replace SQL with NoSQL?  
**A:** No — use **SQL for transactional systems**, **NoSQL for flexible/scalable needs**.

---

## 🔷 16. Database Security

---

### 🔸 Authentication and Authorization

#### ✅ Authentication:

Process of verifying **user identity** (e.g., via username & password, token, certificate)

---

#### ✅ Authorization:

Determining what **actions a user is allowed** to perform

---

#### 📥 Example:

```sql
-- Login
User: ayush | Password: ********

-- Access control
User 'ayush' → can SELECT but not DELETE
```

---

#### 🔍 Diagram:

```
[Login → Auth Check] → [Permission Lookup] → Access Granted/Denied
```

---

### 🔸 Roles and Privileges

#### ✅ Role:

A **named group of privileges** assigned to users

#### ✅ Privilege:

Permission to perform an operation on a DB object (e.g., SELECT on Table)

---

#### 📥 Example:

```sql
CREATE ROLE developer;
GRANT SELECT, INSERT ON Employee TO developer;
GRANT developer TO ayush;
```

---

✅ Easier to manage multiple users with common access patterns

---

### 🔸 SQL Injection

#### ✅ Definition:

An attack that exploits unsanitized inputs to **inject malicious SQL** into queries.

---

#### 📥 Vulnerable Code (❌):

```cpp
string query = "SELECT * FROM Users WHERE name = '" + user_input + "'";
```

If input = `' OR '1'='1`, query becomes:

```sql
SELECT * FROM Users WHERE name = '' OR '1'='1';
```

→ Returns **all users**

---

#### ✅ Prevention:

- Use **prepared statements / parameterized queries**
- Input validation and escaping

---

### 🔸 Data Masking and Encryption

---

#### ✅ Data Masking:

Hide sensitive information while retaining data format

📥 Example:

```
Original SSN: 123-45-6789
Masked: XXX-XX-6789
```

---

#### ✅ Data Encryption:

Use cryptographic algorithms to **protect data at rest and in transit**

- **At-rest**: AES-256 for disk-level encryption
- **In-transit**: TLS/SSL for secure client-server communication

---

#### 🔍 Use Cases:

- Compliance (GDPR, HIPAA)
- Protect PII (personally identifiable info)

---

### 🔸 Audit Trails

#### ✅ Definition:

Maintain a **log of all access and modifications** to sensitive data

---

#### ✅ Captures:

- Who accessed/modified data
- What operation was performed
- Timestamp of action

---

#### 📥 Example:

```text
[2025-07-27 09:31] User 'ayush' updated Salary in Employee
```

---

✅ Used for:

- Forensics
- Compliance reporting
- Monitoring unauthorized access

---

### 🔸 GRANT and REVOKE

---

#### ✅ GRANT:

Give users **specific privileges**

```sql
GRANT SELECT, INSERT ON Employee TO ayush;
```

---

#### ✅ REVOKE:

Remove previously granted privileges

```sql
REVOKE INSERT ON Employee FROM ayush;
```

---

✅ Used to control access at a **fine-grained level**

---

#### 🌐 Real-World Q&A:

**Q:** Can roles be nested?  
**A:** Yes — roles can be granted to other roles in systems like PostgreSQL.

**Q:** Why use masking over encryption?  
**A:** Masking is for **display protection**, encryption is for **secure storage**.

**Q:** How do audit logs differ from transaction logs?  
**A:** Audit logs track **who did what**, while transaction logs track **data changes** for recovery.

---

## 🔷 17. Miscellaneous & Practical Topics

---

### 🔸 Database Sharding

#### ✅ Definition:

Sharding is a **horizontal partitioning** technique where a large database is split into **smaller, faster, and more manageable pieces**, called **shards**, spread across multiple servers.

---

#### 📥 Example:

```
Users 1–1000  → Shard A
Users 1001–2000 → Shard B
```

Each shard is an **independent database instance**

---

#### 🔍 Diagram:

```
          ┌────────────┐
          │  App Tier  │
          └────┬───────┘
               │
        ┌──────┼───────┐
     [Shard 1] [Shard 2] ...
```

---

✅ Pros:

- Improved **performance**
- Better **scalability**
- **Fault isolation**

❌ Cons:

- Complex **cross-shard queries**
- Harder **transaction consistency**

---

### 🔸 Database Federation

#### ✅ Definition:

A **federated database system** integrates multiple autonomous databases into a single system while maintaining their **autonomy**.

---

#### ✅ Features:

- Each database is independently managed
- Users can access data across systems **transparently**

---

#### 📥 Example:

- Oracle DB in Europe + MySQL DB in US
  → Queried using a **virtual schema**

---

#### 🔍 Use Case:

- Cross-organization data access
- Vendor-diverse database ecosystems

---

✅ Pros:

- No need to merge databases
- Keeps legacy systems intact

❌ Cons:

- Performance overhead
- Inconsistent schema handling

---

### 🔸 Event Sourcing and CQRS

---

#### ✅ Event Sourcing:

Stores **every change to data as an event**, instead of just the latest state.

---

#### 📥 Example:

Instead of:

```json
{ "balance": 500 }
```

You store:

```json
[
  { "event": "Deposit", "amount": 200 },
  { "event": "Withdraw", "amount": 100 }
]
```

→ Current state derived by replaying events

---

#### ✅ CQRS (Command Query Responsibility Segregation):

- **Commands** change data
- **Queries** read data

✅ Separation allows optimization and scaling of read/write workloads

---

#### 🔍 Diagram:

```
[Client]
  ├── Command → [Write Model]
  └── Query  → [Read Model]
```

---

✅ Use Case:

- Event-driven architectures
- Microservices
- Auditability and temporal data reconstruction

---

### 🔸 ORM (Object Relational Mapping)

#### ✅ Definition:

ORM maps **object-oriented classes** to **relational database tables**, allowing developers to interact with DB using their language's native objects.

---

#### 📥 Example (Hibernate / Java):

```java
@Entity
class Employee {
  @Id
  private int id;
  private String name;
}
```

→ Automatically mapped to SQL table `Employee`

---

#### ✅ Popular ORM Tools:

- **Hibernate** (Java)
- **JPA** – Java Persistence API
- **SQLAlchemy** (Python)
- **Entity Framework** (.NET)
- **Sequelize** (Node.js)

---

#### ✅ Benefits:

- Cleaner code, no SQL boilerplate
- Abstraction layer over JDBC/ODBC
- Support for **lazy loading**, **caching**, and **transactions**

❌ Drawbacks:

- Less control over raw queries
- Performance overhead in complex joins

---

#### 🌐 Real-World Q&A:

**Q:** Is ORM a replacement for SQL?  
**A:** No — it simplifies interaction but may still require native queries.

**Q:** When is CQRS beneficial?  
**A:** High-read applications, where **read and write models** differ in structure or scale.

**Q:** How is event sourcing different from audit logs?  
**A:** Event sourcing **builds state from events**, whereas audit logs just **record changes**.

---

### 🔸 Backups and Snapshots

#### ✅ Backups:

A **copy of database data** taken periodically to prevent data loss.

- Can be **full**, **incremental**, or **differential**
- Stored on **cloud, tape, or local disk**

---

#### ✅ Snapshots:

A **point-in-time copy** of a database or volume, often using **copy-on-write** technique.

- Faster than backups
- Used for short-term recovery or testing

---

#### 📥 Example:

- `mysqldump` for MySQL backups
- AWS RDS snapshot: `rds:CreateDBSnapshot`

---

#### 🔍 Diagram:

```
Time →
[Snapshot] ── [Changes]
[Backup]   ─────────────
```

---

### 🔸 Schema Migration

#### ✅ Definition:

Process of **updating database schema** (e.g., add column, modify type) in a version-controlled and safe manner.

---

#### 📥 Example:

```sql
ALTER TABLE Employee ADD COLUMN experience INT;
```

✅ Schema migration tools:

- Flyway
- Liquibase
- Alembic (Python)
- Prisma Migrate

---

#### ✅ Best Practices:

- Use transactional DDL if supported
- Version your migrations
- Backward compatibility for rolling deploys

---

### 🔸 Read Replicas, Failover, High Availability

---

#### ✅ Read Replicas:

Copies of a DB instance used for **read-only** queries.

- Reduces load on master
- Asynchronous replication

📥 Example: PostgreSQL or AWS RDS Read Replica

---

#### ✅ Failover:

Automatic or manual switch to **standby DB** if the primary fails.

- Increases **availability**

---

#### ✅ High Availability (HA):

Ensures **minimal downtime** via:

- Replication
- Load balancers
- Clustered DB setups (e.g., Galera, Patroni)

---

#### 🔍 Diagram:

```
      ┌────────────┐
      │ Load Balancer │
      └──────┬───────┘
     ┌───────┴────────┐
 Primary        Replica(s)
```

---

### 🔸 Real-Time vs Batch Processing

---

| Aspect      | Real-Time Processing          | Batch Processing                  |
| ----------- | ----------------------------- | --------------------------------- |
| Latency     | Low (ms-sec)                  | High (minutes-hours)              |
| Data Volume | Continuous small amounts      | Large datasets                    |
| Example     | Fraud detection, live metrics | Payroll, monthly billing reports  |
| Tools       | Kafka, Flink, Spark Streaming | Hadoop, Apache Spark (batch mode) |

---

#### 📥 Example:

- Real-Time: Alert when unusual login detected
- Batch: Generate sales report every 24 hours

---

### 🔸 OLAP vs OLTP

---

| Feature       | OLTP                              | OLAP                           |
| ------------- | --------------------------------- | ------------------------------ |
| Stands for    | Online Transaction Processing     | Online Analytical Processing   |
| Purpose       | CRUD transactions (insert/update) | Analysis and reporting         |
| Data Volume   | Small, frequent transactions      | Large, historical data         |
| Query Type    | Simple, fast                      | Complex aggregations           |
| Normalization | Highly normalized                 | Often denormalized/star schema |
| Examples      | Banking, E-commerce               | BI dashboards, Data warehouses |

---

#### 📥 Example:

- OLTP: `UPDATE Balance SET amount = 200 WHERE acc_id = 101;`
- OLAP: `SELECT region, SUM(sales) FROM Orders GROUP BY region;`

---

#### 🌐 Real-World Q&A:

**Q:** Why use read replicas?  
**A:** To offload read traffic and improve performance in scaling.

**Q:** How do backups differ from snapshots?  
**A:** Backups are durable, portable; snapshots are fast, ephemeral.

**Q:** Can OLAP and OLTP coexist?  
**A:** Yes — via hybrid systems (HTAP), or using ETL to sync OLTP → OLAP.

---

### 🔸 ETL Process

#### ✅ Definition:

**ETL (Extract, Transform, Load)** is a data integration process used to **move and process data** from multiple sources into a centralized system (e.g., data warehouse).

---

#### 📥 Steps:

1. **Extract** – Pull raw data from various sources (DBs, files, APIs)
2. **Transform** – Clean, validate, normalize, aggregate
3. **Load** – Insert into target system (e.g., warehouse)

---

#### 🔍 Diagram:

```
[Source Systems]
     ↓
   Extract
     ↓
 Transform
     ↓
   Load
     ↓
[Data Warehouse]
```

---

✅ Tools: Apache NiFi, Talend, Informatica, Airbyte, custom scripts (Python/Pandas)

---

### 🔸 Data Warehousing

#### ✅ Definition:

A **data warehouse** is a central repository for **integrated, historical, and analytical data**, designed for **querying and reporting**.

---

#### ✅ Characteristics:

- Optimized for **read-heavy analytics**
- Supports **OLAP** operations
- Stores **denormalized** data (e.g., star schema)
- Subject-oriented, time-variant

---

#### 📥 Example:

Data warehouse for a retail company with:

- Sales, customers, inventory, location → integrated for reporting

---

✅ Tools: Amazon Redshift, Snowflake, Google BigQuery, Teradata

---

### 🔸 Materialized Views

#### ✅ Definition:

A **materialized view** stores the **physical result** of a query, unlike normal views which are virtual.

---

#### 📥 Example:

```sql
CREATE MATERIALIZED VIEW MonthlySales AS
SELECT region, SUM(sales) FROM Orders GROUP BY region;
```

→ Refreshable and indexable

---

#### ✅ Use Cases:

- Dashboards
- Precomputed aggregations
- Improving expensive query performance

---

#### 🔍 Commands:

```sql
REFRESH MATERIALIZED VIEW MonthlySales;
DROP MATERIALIZED VIEW MonthlySales;
```

---

### 🔸 Time-Series Databases

#### ✅ Definition:

A **time-series database (TSDB)** is optimized to handle **data indexed by time**, such as logs, metrics, and sensor data.

---

#### ✅ Features:

- High write throughput
- Compression and downsampling
- Retention policies
- Time-window queries (e.g., last 5 mins)

---

#### 📥 Example:

```text
timestamp        temperature
----------------------------
2025-07-27 00:00   32.1
2025-07-27 00:01   32.3
```

---

✅ Use Cases:

- IoT devices
- Monitoring systems (Prometheus, Grafana)
- Financial tick data

✅ Popular Tools:

- InfluxDB, TimescaleDB, Prometheus, OpenTSDB

---

#### 🌐 Real-World Q&A:

**Q:** How is ETL different from ELT?  
**A:** ELT performs **load first, then transform** inside the warehouse (common in cloud systems).

**Q:** Why use materialized views?  
**A:** To improve performance of repetitive, expensive queries.

**Q:** How is TSDB different from normal DB?  
**A:** TSDBs are optimized for **append-only, time-stamped** data and allow better retention/query support.

---

## 🔷 18. Interview-Oriented Practice

---

### 🔸 Normalize a Given Schema to 3NF / BCNF

#### 📥 Problem:

Given a relation:  
`Student(ID, Name, Branch, HOD, HOD_Dept)`

And FDs:

```
ID → Name, Branch
Branch → HOD
HOD → HOD_Dept
```

---

#### ✅ Step-by-step to 3NF:

1. **FD1: ID → Name, Branch** → Keep `Student(ID, Name, Branch)`
2. **FD2: Branch → HOD** → New relation: `Branch_HOD(Branch, HOD)`
3. **FD3: HOD → HOD_Dept** → New relation: `HOD_Dept(HOD, HOD_Dept)`

---

✅ Final 3NF:

```
Student(ID, Name, Branch)
Branch_HOD(Branch, HOD)
HOD_Dept(HOD, HOD_Dept)
```

---

### 🔸 Write SQL Queries

#### ✅ Easy

```sql
SELECT name FROM Employee WHERE salary > 50000;
```

#### ✅ Subquery

```sql
SELECT name FROM Employee
WHERE salary > (SELECT AVG(salary) FROM Employee);
```

#### ✅ Join

```sql
SELECT E.name, D.name
FROM Employee E
JOIN Department D ON E.dept_id = D.id;
```

#### ✅ Window Function

```sql
SELECT name, salary,
       RANK() OVER (PARTITION BY dept_id ORDER BY salary DESC) AS dept_rank
FROM Employee;
```

---

### 🔸 ER to Relational Conversion

#### 📥 ER Example:

```
Entity: Student (ID, Name)
Entity: Course (CID, Title)
Relationship: Enrolled (Grade)
```

---

#### ✅ Conversion:

```
Student(ID PRIMARY KEY, Name)
Course(CID PRIMARY KEY, Title)
Enrolled(ID, CID, Grade, PRIMARY KEY(ID, CID),
         FOREIGN KEY(ID) REFERENCES Student,
         FOREIGN KEY(CID) REFERENCES Course)
```

---

### 🔸 Explain Transaction Anomalies and Fix Them

---

#### 📥 Example: Dirty Read

T1 reads uncommitted update from T2.

```text
T1: READ(Balance) → 100
T2: UPDATE Balance = 200
T1: READ(Balance) → 200 (Dirty Read)
T2: ROLLBACK
```

---

✅ Fix: Use **isolation levels** like `READ COMMITTED`, `REPEATABLE READ`

---

| Anomaly             | Fix                                 |
| ------------------- | ----------------------------------- |
| Dirty Read          | Use READ COMMITTED / higher         |
| Non-repeatable Read | Use REPEATABLE READ / SERIALIZABLE  |
| Phantom Read        | Use SERIALIZABLE or predicate locks |

---

#### 🌐 Real-World Q&A:

**Q:** How do you check if a schema is in BCNF?  
**A:** For each FD X → Y, check if **X is a superkey**. If not, decompose.

**Q:** How do you fix anomalies in SQL?  
**A:** Use proper **isolation levels**, locks, and ACID-compliant transactions.

**Q:** What's the trick to converting ER to relational schema?  
**A:** Convert entities to tables, relationships to foreign keys, and apply cardinality rules.

---

### 🔸 Implement a Mini Relational DBMS (Theoretical)

#### ✅ Core Components:

1. **Parser** – Parses SQL-like commands (`SELECT`, `INSERT`, etc.)
2. **Catalog Manager** – Stores metadata (tables, schemas, indexes)
3. **Storage Engine** – Manages physical data (files, pages, blocks)
4. **Query Processor** – Executes parsed queries using relational algebra
5. **Transaction Manager** – Ensures ACID via WAL or undo logging
6. **Buffer Manager** – Caches frequently accessed data pages

---

#### 🔧 Theoretical Architecture:

```
[User SQL] → [Parser] → [Query Processor] → [Execution Plan]
                                 ↓
                    [Buffer Manager] ↔ [Disk Pages]
                                 ↓
                       [Transaction Log / WAL]
```

---

✅ Concepts to simulate:

- Basic schema creation (`CREATE TABLE`)
- Query execution via in-memory hash/array
- Support for `SELECT`, `WHERE`, `JOIN`
- Naive indexing (e.g., hashmap for B+ Tree)

---

### 🔸 Design a Scalable DB (System Design Context)

---

#### ✅ Requirements to Consider:

- High write throughput (millions of inserts/sec)
- Global read latency < 100 ms
- Horizontal scalability
- Fault-tolerance & backups

---

#### 🔍 Design Components:

- **Sharding** → Partition data by user ID, geo, or hash
- **Replication** → Primary + multiple replicas for HA
- **Indexes** → B+ Trees or Inverted Index
- **Caching Layer** → Redis/Memcached for read performance
- **Write Path** → WAL → Memtable → SSTable (like LSM Trees in Cassandra)
- **Query Engine** → Handles secondary indexes, aggregations

---

✅ Architecture Sample:

```
                        [Client]
                           ↓
                      [API Layer]
                           ↓
               ┌─────────Write Proxy──────────┐
        [Shard 1 - Primary]          [Shard 2 - Primary]
               ↓                             ↓
       [Replica 1] [Replica 2]     [Replica 1] [Replica 2]
```

---

### 🔸 How Indexes Help in Query Optimization

---

#### ✅ Without Index:

```sql
SELECT * FROM Employee WHERE emp_id = 101;
```

→ **Full table scan** (O(n))

---

#### ✅ With Index:

- Use B+ Tree or Hash Index on `emp_id`
- **Reduces lookup to O(log n)**

---

#### 📥 Example:

```sql
CREATE INDEX idx_emp_id ON Employee(emp_id);
```

---

#### ✅ Query Plan Comparison:

```sql
EXPLAIN SELECT * FROM Employee WHERE emp_id = 101;
```

- Without Index → Seq Scan
- With Index → Index Scan

---

#### 🔍 Types of Indexes:

- **Clustered**: Data stored in order of index
- **Non-clustered**: Separate structure, holds pointers
- **Composite**: Multiple columns (emp_id, name)
- **Covering Index**: All required fields in index itself

---

✅ Used to:

- Avoid full scans
- Speed up JOINs, WHEREs, ORDER BYs

---

### 🔸 ACID vs BASE (with Examples)

---

| Property    | ACID (SQL DBs)                         | BASE (NoSQL / Distributed)     |
| ----------- | -------------------------------------- | ------------------------------ |
| Atomicity   | All or nothing                         | Partial updates may be visible |
| Consistency | Always valid state                     | Eventually consistent          |
| Isolation   | Concurrent transactions don’t conflict | Less strict isolation          |
| Durability  | Data persists after commit             | Durability may be eventual     |
| Use Case    | Banking, Inventory                     | Web-scale apps, social media   |

---

#### ✅ ACID Example:

```sql
BEGIN;
UPDATE accounts SET balance = balance - 100 WHERE id = 1;
UPDATE accounts SET balance = balance + 100 WHERE id = 2;
COMMIT;
```

→ Money moved only if both operations succeed

---

#### ✅ BASE Example:

- NoSQL DB (e.g., DynamoDB)
- Updates are propagated to replicas asynchronously
- Clients may see stale data briefly

---

#### 🌐 Real-World Q&A:

**Q:** Why not always use ACID?  
**A:** Hard to scale ACID in distributed systems; BASE provides better availability.

**Q:** Can BASE systems support transactions?  
**A:** Some NoSQL DBs now offer **multi-document or pseudo-transaction** support (e.g., MongoDB v4+).

**Q:** When would you avoid indexes?  
**A:** On write-heavy columns, or when data is too small to benefit.

---
