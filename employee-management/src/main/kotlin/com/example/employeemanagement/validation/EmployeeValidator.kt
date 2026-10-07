package com.example.employeemanagement.validation

import com.example.employeemanagement.domain.model.Employee
import com.example.employeemanagement.exception.ValidationException

object EmployeeValidator {

    private val emailRegex = Regex("^[^@\\s]+@[^@\\s]+\\.[^@\\s]+$")

    fun validate(employee: Employee) {
        if (employee.employeeId <= 0) {
            throw ValidationException("Employee ID must be greater than zero.")
        }
        if (employee.firstName.isBlank()) {
            throw ValidationException("First name is required.")
        }
        if (employee.lastName.isBlank()) {
            throw ValidationException("Last name is required.")
        }
        if (employee.email.isBlank() || !emailRegex.matches(employee.email)) {
            throw ValidationException("Valid email is required.")
        }
        if (employee.department.isBlank()) {
            throw ValidationException("Department is required.")
        }
        if (employee.jobTitle.isBlank()) {
            throw ValidationException("Job title is required.")
        }
    }
}
