package com.example.employeemanagement.domain.model

data class Employee(
    val employeeId: Int,
    var firstName: String,
    var lastName: String,
    var email: String,
    var department: String,
    var jobTitle: String,
    var status: EmploymentStatus
)
