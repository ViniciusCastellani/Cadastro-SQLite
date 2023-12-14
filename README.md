# C++ SQLite Contact Management System

This C++ program utilizes SQLite to manage contact information, allowing users to perform CRUD (Create, Read, Update, Delete) operations on a contact database.

## Description

The code consists of functionalities that enable the following operations:

### 1. Insert Data

- Collects contact details such as name, address, email, phone numbers, CPF, and RG (Brazillian identification documents).

### 2. List Data

- Displays a list of all contacts stored in the database.

### 3. View Specific Data

- Allows the user to view a specific contact based on the provided ID.

### 4. Update Data

- Enables modifications to existing contact details based on the chosen ID.

### 5. Delete Data

- Removes a contact from the database based on the provided ID.

## Code Overview

### Functions Included:

- `inserir`: Adds new contact information to the database.
- `listar`: Lists all contacts stored in the database.
- `consulta`: Views a specific contact information based on the provided ID.
- `alterar`: Modifies existing contact information based on the chosen ID.
- `excluir`: Deletes a contact from the database based on the provided ID.
- `matar`: Drops the entire `contatos` table, deleting all stored data.

### Database Structure

The code sets up an SQLite database table named `contatos` with the following columns:
- `id` (auto-incremented primary key)
- `nome` (name)
- `rua` (street)
- `bairro` (neighborhood)
- `estado` (state)
- `email`
- `cep` (zip code)
- `celular` (phone number)
- `cpf` (Brazilian taxpayer registry number)
- `rg` (Brazilian identification document)

## Execution

- The code utilizes the SQLite library and should be compiled with appropriate linkages to the SQLite C library.
- Upon execution, the user can interact with the menu-driven system to perform various operations on the contact database.

