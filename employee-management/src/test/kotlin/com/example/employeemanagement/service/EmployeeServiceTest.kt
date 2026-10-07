package com.example.employeemanagement.service

import com.example.employeemanagement.domain.model.Employee
import com.example.employeemanagement.domain.model.EmploymentStatus
import com.example.employeemanagement.exception.DuplicateEmployeeException
import com.example.employeemanagement.exception.EmployeeNotFoundException
import com.example.employeemanagement.exception.ValidationException
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertFailsWith
import kotlin.test.assertTrue

class EmployeeServiceTest {

    private fun createService() = EmployeeService()

    private fun createEmployee(
        id: Int = 1,
        email: String = "john.doe@example.com"
    ) = Employee(
        employeeId = id,
        firstName = "John",
        lastName = "Doe",
        email = email,
        department = "IT",
        jobTitle = "Engineer",
        status = EmploymentStatus.ACTIVE
    )

    @Test
    fun `should add employee successfully`() {
        val service = createService()
        val employee = createEmployee()

        assertEquals(employee, service.addEmployee(employee))
    }

    @Test
    fun `should reject duplicate employee id`() {
        val service = createService()
        service.addEmployee(createEmployee(id = 1))

        assertFailsWith<DuplicateEmployeeException> {
            service.addEmployee(createEmployee(id = 1, email = "other@example.com"))
        }
    }

    @Test
    fun `should reject duplicate email ignoring case`() {
        val service = createService()
        service.addEmployee(createEmployee(email = "john@example.com"))

        assertFailsWith<DuplicateEmployeeException> {
            service.addEmployee(createEmployee(id = 2, email = "JOHN@example.com"))
        }
    }

    @Test
    fun `should retrieve employee by id`() {
        val service = createService()
        val employee = createEmployee()
        service.addEmployee(employee)

        assertEquals(employee, service.getEmployeeById(1))
    }

    @Test
    fun `should update employee`() {
        val service = createService()
        val employee = createEmployee()
        service.addEmployee(employee)

        val updated = employee.copy(firstName = "Jane", department = "HR")
        val result = service.updateEmployee(1, updated)

        assertEquals("Jane", result.firstName)
        assertEquals("HR", result.department)
    }

    @Test
    fun `should delete employee`() {
        val service = createService()
        service.addEmployee(createEmployee())

        assertTrue(service.deleteEmployee(1))
        assertFailsWith<EmployeeNotFoundException> { service.getEmployeeById(1) }
    }

    @Test
    fun `should throw when employee not found`() {
        val service = createService()
        assertFailsWith<EmployeeNotFoundException> { service.getEmployeeById(999) }
    }

    @Test
    fun `should validate email`() {
        val service = createService()

        assertFailsWith<ValidationException> {
            service.addEmployee(createEmployee(email = "invalid-email"))
        }
    }
}
