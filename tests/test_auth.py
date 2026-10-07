def test_login_success(client):
    response = client.post("/api/v1/auth/login", json={"username": "admin", "password": "admin-pass"})
    assert response.status_code == 200
    assert response.json()["token_type"] == "bearer"
    assert response.json()["access_token"]

def test_login_rejects_bad_password(client):
    response = client.post("/api/v1/auth/login", json={"username": "admin", "password": "wrong"})
    assert response.status_code == 401
