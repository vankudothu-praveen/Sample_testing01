package com.example.employeemanagement.service

import com.example.employeemanagement.domain.model.Employee
import com.example.employeemanagement.exception.DuplicateEmployeeException
import com.example.employeemanagement.exception.EmployeeNotFoundException
import com.example.employeemanagement.validation.EmployeeValidator

class EmployeeService {

    private val employees = mutableListOf<Employee>()

    fun addEmployee(employee: Employee): Employee {
        EmployeeValidator.validate(employee)

        if (employees.any { it.employeeId == employee.employeeId }) {
            throw DuplicateEmployeeException("Employee ID already exists.")
        }
        if (employees.any { it.email.equals(employee.email, ignoreCase = true) }) {
            throw DuplicateEmployeeException("Employee email already exists.")
        }

        employees.add(employee)
        return employee
    }

    fun getEmployeeById(employeeId: Int): Employee =
        employees.firstOrNull { it.employeeId == employeeId }
            ?: throw EmployeeNotFoundException("Employee not found.")

    fun getAllEmployees(): List<Employee> = employees.toList()

    fun updateEmployee(employeeId: Int, updatedEmployee: Employee): Employee {
        EmployeeValidator.validate(updatedEmployee)
        val existingEmployee = getEmployeeById(employeeId)

        if (updatedEmployee.employeeId != employeeId) {
            throw IllegalArgumentException("Updated employee ID must match the requested employee ID.")
        }
        if (employees.any {
                it.employeeId != employeeId &&
                    it.email.equals(updatedEmployee.email, ignoreCase = true)
            }
        ) {
            throw DuplicateEmployeeException("Employee email already exists.")
        }

        existingEmployee.firstName = updatedEmployee.firstName
        existingEmployee.lastName = updatedEmployee.lastName
        existingEmployee.email = updatedEmployee.email
        existingEmployee.department = updatedEmployee.department
        existingEmployee.jobTitle = updatedEmployee.jobTitle
        existingEmployee.status = updatedEmployee.status

        return existingEmployee
    }

    fun deleteEmployee(employeeId: Int): Boolean {
        val employee = getEmployeeById(employeeId)
        return employees.remove(employee)
    }
}
