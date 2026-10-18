# Phone Book Application (Java)

A console-based phone and contacts management application built as a university assignment in Java.

## What it does

- Models phones, contacts, and phone numbers as objects
- Stores contacts in a generic list container (`ListaStavki<Stavka>`)
- Supports adding, finding, and displaying contacts and their numbers
- Raises custom exceptions for missing entries

## Key concepts demonstrated

| Concept | Implementation detail |
|---------|-----------------------|
| OOP modelling | `Telefon`, `Imenik`, `Kontakt`, `Broj` — separate classes with clear domain roles |
| Generic collections | `ListaStavki<T>` — a custom generic list wrapping Java collection |
| Custom exceptions | `GNePostoji` thrown when a contact or number is not found |
| Encapsulation | Private fields with getters/setters on all model classes |
| Separation of concerns | `Tastatura` handles all console I/O; business logic stays in model classes |

## Building & running

```bash
javac *.java
java Telefoni
```
