use whatever
INSERT INTO team (description)
VALUES
    ('desc1'), ('desc2'), ('descK')

INSERT INTO project (name)
VALUES
    ('name1'), ('name2'), ('nameJ')

select * from team
select * from project

delete from team
delete from project

drop table team
drop table project
drop table takesPartIn


INSERT INTO takesPartIn (teamid, projectid)
values (1, 2), (3, 3), (2, 3)

select * from takesPartIn


delete from takesPartIn


-- dirty read: a transaction reads data that has been modified by another transaction, but not yet committed. 
-- read uncommitted: This level allows transactions to read uncommitted data from other transactions, leading to potential dirty reads.
set transaction isolation level read uncommitted
begin tran
update team
set description = 'updatedDesc1'
where id = 1
exec sp_log_changes 'Modify description `updatedDesc1` where id is 1', 'Dirty reads 1: update'
exec sp_log_locks 'Dirty reads 1: after update'
waitfor delay '00:00:05'
rollback 


-- solution: read committed for dirty reads
set transaction isolation level read committed
begin tran
update team
set description = 'updatedDesc1'
where id = 1
exec sp_log_changes 'Modify description `updatedDesc1` where id is 1', 'Dirty reads 1: update'
exec sp_log_locks 'Dirty reads 1: after update'
waitfor delay '00:00:05'
rollback 


select * from project
-- non-repeatable reads - Non Repeatable read occurs when a transaction reads the same row twice and gets a different value each time.
set transaction isolation level read committed
insert into project(name) values('nameInsertedNew')
begin tran
waitfor delay '00:00:05'
update project
set name = 'nameModified1'
where id = 4
exec sp_log_changes 'Modify project name to first where id is 4', 'Non-Repeatable reads 1: update'
exec sp_log_locks 'Non-Repeatable reads 1: after update'
commit tran

-- solution: repeatable read
select * from project
set transaction isolation level repeatable read
insert into project(name) values('nameInsertedNewSolution')
begin tran
waitfor delay '00:00:05'
update project
set name = 'nameModified2'
where id = 5
exec sp_log_changes 'Modify name where id is 5', 'Repeatable reads 1: update'
exec sp_log_locks 'Repeatable reads 1: after update'
commit tran

-- phantom reads - The Phantom Read concurrency problem in SQL Server occurs in a scenario where a transaction 
-- reads rows from a database table, and then, in the course of the same transaction, a subsequent read returns 
-- a set of rows that includes rows that were not visible in the first read.

select * from team
set transaction isolation level repeatable read
begin tran
waitfor delay '00:00:05'
insert into team values('descNewPhantom AAAAAAA')
exec sp_log_changes 'Insert new team', 'Phantom reads 1: insert'
exec sp_log_locks 'Phantom reads 1: after insert'
commit tran

-- solution for phantom reads: serializable - guarantees that even though transactions may execute in parallel,
-- the result is the same as if they had executed one at a time, without any concurrency

set transaction isolation level serializable
begin tran
waitfor delay '00:00:05'
insert into team values('descAddedSolvingPhantomUsingSerializable')
exec sp_log_changes 'Insert new project', 'Phantom reads 1 Serializable: insert'
exec sp_log_locks 'Phantom reads 1 Serializable: after insert'
commit tran

-- deadlock - occurs when two or more tasks permanently block each other by each task having a lock on a resource
-- that the other tasks are trying to lock.
select * from project
begin tran
update team set description = 'setDescriptionDeadlock' where id = 4
exec sp_log_changes 'Modify team desc where id is 4', 'Deadlock 1: first update'
exec sp_log_locks 'Deadlock 1: between updates'
waitfor delay '00:00:05'
update project set name = 'newNameDeadlock' where id = 5
exec sp_log_changes 'Modify project name where id W004', 'Deadlock 1: second update'
commit tran


-- solution for deadlock: set deadlock_priority
set deadlock_priority 1 
begin tran
update team set description = 'modifiedDeadlockSolution' where id = 5
exec sp_log_changes 'Modify team desc where id is 5', 'Deadlock Prevention 1: first update'
exec sp_log_locks 'Deadlock Prevention 1: between updates'
waitfor delay '00:00:05'
update project set name = 'newNameDeadlockSolution' where id = 5
exec sp_log_changes 'Modify project name where id is 5', 'Deadlock Prevention 1: second update'
commit tran

select * from team
select * from project

-- update conflict

alter database whatever set allow_snapshot_isolation ON

begin tran
waitfor delay '00:00:05'
update team
set description = 'changedDescLast'
where id = 3
exec sp_log_changes 'Modify team desc to "changedDescLast" where id is 3', 'Update conflict 1: update'
exec sp_log_locks 'Update conflict 1: after update'
commit tran

select * from team
select * from project