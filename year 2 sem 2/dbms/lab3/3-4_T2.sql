-- dirty read
use whatever
set transaction isolation level read uncommitted
begin tran
select *
from team
exec sp_log_locks 'Dirty reads 2: after first select'
waitfor delay '00:00:05'
select *
from team
exec sp_log_locks 'Dirty reads 2: after second select'
commit tran 

--solution: read committed for dirty reads
set transaction isolation level read committed
begin tran
select *
from team
exec sp_log_locks 'Dirty reads 2 Prevention: after first select'
waitfor delay '00:00:05'
select *
from team
exec sp_log_locks 'Dirty reads 2 Prevention: after second select'
commit tran 

-- non-repeatable reads
set transaction isolation level read committed
begin tran
select *
from project
exec sp_log_locks 'Non-Repeatable reads 2: after first select'
waitfor delay '00:00:05'
select *
from project
exec sp_log_locks 'Non-Repeatable reads 2: after second select'
commit tran

-- solution: repeatable read for unrepeatable reads

set transaction isolation level repeatable read
begin tran
select *
from project
exec sp_log_locks 'Repeatable reads 2: after first select'
waitfor delay '00:00:05'
select *
from project
exec sp_log_locks 'Repeatable reads 2: after second select'
commit tran

-- phantom reads

set transaction isolation level repeatable read
begin tran
select *
from team
exec sp_log_locks 'Phantom reads 2: after first select'
waitfor delay '00:00:15'
select *
from team
exec sp_log_locks 'Phantom reads 2: after second select'
commit tran 
-- solution
set transaction isolation level serializable
begin tran
select *
from team
exec sp_log_locks 'Phantom reads 2 Serializable: after first select'
waitfor delay '00:00:05'
select *
from team
exec sp_log_locks 'Phantom reads 2 Serializable: after second select'
commit tran 

-- deadlock

begin tran
update project set name = 'deadlockHere' where id = 5
exec sp_log_changes 'Modify project name where id is 4', 'Deadlock 2: first update'
exec sp_log_locks 'Deadlock 2: between updates'
waitfor delay '00:00:05'
update team set description = 'setNewDescDeadlock' where id = 4
exec sp_log_changes 'Modify employee name where id is E001', 'Deadlock 2: second update'
commit tran

-- update conflict 

set tran isolation level snapshot
begin tran
waitfor delay '00:00:05'
update team
set description = 'changedDescLast222222'
where id = 3
exec sp_log_changes 'Modify team desc to "changedDescLast222222" where id is 3', 'Update conflict 2: update'
exec sp_log_locks 'Update conflict 2: after update'
commit tran

select * from team
select * from project