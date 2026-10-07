def test_create_employee_and_duplicate_email(client, employee_payload):
    created = client.post("/api/v1/employees", json=employee_payload, headers=client.admin_headers)
    assert created.status_code == 201
    assert created.json()["employee_id"] == 1
    duplicate = client.post("/api/v1/employees", json=employee_payload, headers=client.admin_headers)
    assert duplicate.status_code == 409

def test_employee_read_and_regular_user_forbidden_from_writes(client, employee_payload):
    created = client.post("/api/v1/employees", json=employee_payload, headers=client.admin_headers)
    employee_id = created.json()["employee_id"]
    read = client.get(f"/api/v1/employees/{employee_id}", headers=client.user_headers)
    assert read.status_code == 200
    forbidden = client.delete(f"/api/v1/employees/{employee_id}", headers=client.user_headers)
    assert forbidden.status_code == 403

def test_update_list_filter_and_delete(client, employee_payload):
    created = client.post("/api/v1/employees", json=employee_payload, headers=client.admin_headers)
    employee_id = created.json()["employee_id"]
    updated = client.put(f"/api/v1/employees/{employee_id}", json={"department": "Research"}, headers=client.admin_headers)
    assert updated.status_code == 200
    assert updated.json()["department"] == "Research"
    listed = client.get("/api/v1/employees?page=1&page_size=10&department=Research", headers=client.user_headers)
    assert listed.status_code == 200
    assert listed.json()["pagination"]["total_records"] == 1
    deleted = client.delete(f"/api/v1/employees/{employee_id}", headers=client.admin_headers)
    assert deleted.status_code == 204

def test_validation_and_missing_employee(client, employee_payload):
    employee_payload["email"] = "not-an-email"
    invalid = client.post("/api/v1/employees", json=employee_payload, headers=client.admin_headers)
    assert invalid.status_code == 422
    missing = client.get("/api/v1/employees/999", headers=client.user_headers)
    assert missing.status_code == 404

def test_write_requires_authentication(client, employee_payload):
    response = client.post("/api/v1/employees", json=employee_payload)
    assert response.status_code == 401
