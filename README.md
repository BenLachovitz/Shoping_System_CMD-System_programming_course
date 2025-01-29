
# Supermarket Management System
A command-line based supermarket management system implemented in C, focusing on advanced C programming concepts including string manipulation, function pointers, variable pointers, structs, preprocessor directives, and file handling.

## Features
### Supermarket Information Display
- View supermarket details (name and address) stored in binary file
- Display complete product inventory
  - Barcode
  - Product type
  - Price
  - Stock quantity
- List all customers with their:
  - Names
  - Shopping frequency
  - Total spending
  - Current cart status

### Product Management
- Add new products to inventory
- Update stock quantities automatically after purchases
- Search products by type
- Display product details using barcode
- Persistent storage of all product data in text files

### Customer Management
- Add new customers to the system
- View customer details
- Sort customers by:
  - Name (alphabetically)
  - Shopping frequency
  - Total money spent
- Search customers by name
- Persistent storage of all customer data in text files

### Shopping System
- Initialize shopping session for specific customer
- Add products to cart using barcode
- Specify quantity for each product
- View current shopping cart contents
- Complete purchase and update inventory
- Automatic update of product and customer files after transactions

### Data Persistence
- Products data managed through text file operations
- Customers information stored and updated in text files
- Supermarket details maintained in binary file
- Real-time file updates for all system operations

## Technical Implementation
### Core C Concepts Used
- Struct data structures
- Function pointers for sorting implementation
- Dynamic memory allocation
- String manipulation
- Pointer arithmetic
- Preprocessor directives (#define, #ifdef)
- Macros
- File I/O operations (both text and binary)

## Academic Context
This project was developed as part of the System Programming Course, demonstrating proficiency in:
- Advanced C programming concepts
- Memory management
- Data structure implementation
- Command-line interface design
- String manipulation
- Pointer usage
- File handling and persistence

## Contributing
This is an academic project completed as coursework. Suggestions for improvements are welcome.
