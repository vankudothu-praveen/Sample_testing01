# EmployeeManagement Kotlin Migration

A Kotlin/JVM and Gradle Kotlin DSL migration of the EmployeeManagement sample. The implementation uses in-memory storage and provides employee CRUD operations, validation, domain exceptions, a console entry point, and unit tests.

## Requirements

- JDK 21
- Gradle (the wrapper can be generated with `gradle wrapper`)

## Run

From this directory:

```shell
gradle run
```

Run tests with:

```shell
gradle test
```

The project uses Kotlin 2.0.21 and JUnit 5. The implementation is synchronous and does not use a database or external application framework.
