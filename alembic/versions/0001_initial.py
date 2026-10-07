"""Create users and employees tables.

Revision ID: 0001_initial
Revises:
"""
from alembic import op
import sqlalchemy as sa

revision = "0001_initial"
down_revision = None
branch_labels = None
depends_on = None

status_enum = sa.Enum("ACTIVE", "INACTIVE", "TERMINATED", name="employmentstatus")
role_enum = sa.Enum("ADMIN", "USER", name="userrole")

def upgrade():
    bind = op.get_bind()
    status_enum.create(bind, checkfirst=True)
    role_enum.create(bind, checkfirst=True)
    op.create_table("users",
        sa.Column("user_id", sa.Integer(), autoincrement=True, nullable=False),
        sa.Column("username", sa.String(length=100), nullable=False),
        sa.Column("password_hash", sa.String(length=255), nullable=False),
        sa.Column("role", role_enum, nullable=False),
        sa.Column("created_at", sa.DateTime(timezone=True), server_default=sa.func.now(), nullable=False),
        sa.PrimaryKeyConstraint("user_id"), sa.UniqueConstraint("username"))
    op.create_table("employees",
        sa.Column("employee_id", sa.Integer(), autoincrement=True, nullable=False),
        sa.Column("first_name", sa.String(length=100), nullable=False),
        sa.Column("last_name", sa.String(length=100), nullable=False),
        sa.Column("email", sa.String(length=255), nullable=False),
        sa.Column("department", sa.String(length=100), nullable=False),
        sa.Column("job_title", sa.String(length=150), nullable=False),
        sa.Column("date_of_joining", sa.Date(), nullable=False),
        sa.Column("employment_status", status_enum, nullable=False),
        sa.Column("created_at", sa.DateTime(timezone=True), server_default=sa.func.now(), nullable=False),
        sa.Column("updated_at", sa.DateTime(timezone=True), server_default=sa.func.now(), nullable=False),
        sa.PrimaryKeyConstraint("employee_id"), sa.UniqueConstraint("email"))
    op.create_index("ix_employees_department", "employees", ["department"])
    op.create_index("ix_employees_employment_status", "employees", ["employment_status"])

def downgrade():
    op.drop_index("ix_employees_employment_status", table_name="employees")
    op.drop_index("ix_employees_department", table_name="employees")
    op.drop_table("employees")
    op.drop_table("users")
    role_enum.drop(op.get_bind(), checkfirst=True)
    status_enum.drop(op.get_bind(), checkfirst=True)
