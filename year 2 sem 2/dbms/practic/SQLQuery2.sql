use whatever

--T2
begin tran
update Channel
	set name = 'SOME OTHER VALUE!' where id = 1
commit tran


use whatever
--t2
set transaction isolation level serializable
begin tran
update Userr set lastName = 'test5' where id = 1
commit tran