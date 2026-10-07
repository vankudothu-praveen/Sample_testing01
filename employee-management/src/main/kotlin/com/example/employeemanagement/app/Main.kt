package com.example.employeemanagement.app

import com.example.employeemanagement.domain.model.Employee
import com.example.employeemanagement.domain.model.EmploymentStatus
import com.example.employeemanagement.service.EmployeeService

fun main() {
    val service = EmployeeService()

    val employee = Employee(
        employeeId = 1,
        firstName = "John",
        lastName = "Doe",
        email = "john.doe@example.com",
        department = "IT",
        jobTitle = "Software Engineer",
        status = EmploymentStatus.ACTIVE
    )

    service.addEmployee(employee)

    val result = service.getEmployeeById(1)
    println("Employee: ${result.firstName} ${result.lastName}")
    println("Email: ${result.email}")
    println("Department: ${result.department}")
    println("Status: ${result.status}")
}
