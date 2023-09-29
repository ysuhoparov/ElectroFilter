
CREATE TABLE history (
	Id integer PRIMARY KEY AUTOINCREMENT,
	timerec datetime,
	field1 BIGINT,
	field2 BIGINT,
	field3 BIGINT,
	field4 BIGINT		
	)

select * from history order by id desc LIMIT 25



CREATE TABLE employees (
	Id integer PRIMARY KEY AUTOINCREMENT,
 	employee varchar
);



CREATE TABLE roles (
	Id integer PRIMARY KEY AUTOINCREMENT,
 	role varchar
);

 alter table employees add roleId integer REFERENCES roles (Id)


CREATE TABLE spares (
	Id integer PRIMARY KEY AUTOINCREMENT,
	spare varchar
	manufacturer varchar
);


CREATE TABLE operative (
	Id integer PRIMARY KEY AUTOINCREMENT,
	date datetime,
	field integer,
	content varchar,
 	employeeId integer NOT NULL REFERENCES employee (Id)
);

CREATE TABLE repairs (
	Id integer PRIMARY KEY AUTOINCREMENT,
	date datetime,
	field integer,
	content varchar,
 	employeeId integer NOT NULL REFERENCES employee (Id),
	spareId integer NOT NULL REFERENCES spare (Id)
);



CREATE TABLE types (
	Id integer PRIMARY KEY AUTOINCREMENT,
 	type varchar
);


CREATE TABLE equipments (
	Id integer PRIMARY KEY AUTOINCREMENT,
 	equipment varchar,
	typeId integer NOT NULL REFERENCES types (Id)
);


CREATE TABLE services (
	Id integer PRIMARY KEY AUTOINCREMENT,
	date datetime,
	field integer,
	content varchar,
	employeeId integer NOT NULL REFERENCES employees (Id),
	equipmentId integer NOT NULL REFERENCES equipments (Id)
);




CREATE UNIQUE INDEX "auth_group_permissions_group_id_permission_id_0cd325b0_uniq" ON "auth_group_permissions" ("group_id", "permission_id");
CREATE INDEX "auth_group_permissions_group_id_b120cbf9" ON "auth_group_permissions" ("group_id");
CREATE INDEX "auth_group_permissions_permission_id_84c5c92e" ON "auth_group_permissions" ("permission_id");
