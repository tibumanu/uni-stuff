use whatever
create table LocksLog(
	time DATETIME,
	info VARCHAR(100),
	resource_type VARCHAR(100),
	request_mode VARCHAR(100),
	request_type VARCHAR(100),
	request_status VARCHAR(100),
	request_session_id INT
);

create table ChangesLog(
	time DATETIME,
	info VARCHAR(100),
	operation VARCHAR(100),
);

GO
create or alter procedure sp_log_locks
	@info VARCHAR(100)
as
begin
	insert into LocksLog(time, info, resource_type, request_mode, request_type, request_status, request_session_id)
	select GETDATE(), @info, resource_type, request_mode, request_type, request_status, request_session_id
	from sys.dm_tran_locks
	where request_owner_type = 'TRANSACTION';
end
GO

create or alter procedure sp_log_changes
	@info VARCHAR(100),
	@operation VARCHAR(100)
as
begin
	insert into ChangesLog(time, info, operation) values
	(GETDATE(), @info, @operation);
end
GO

drop table ChangesLog
drop table LocksLog
select * from LocksLog;
select * from ChangesLog;