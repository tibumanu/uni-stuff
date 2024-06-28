use whatever

create table team(
	id int not null IDENTITY(1,1) primary key,
	description varchar(100)
)

create table project(
	id int not null IDENTITY(1,1) primary key,
	name varchar(100)
)

create table takesPartIn(
	teamid int not null,
	projectid int not null,
	foreign key(teamid)
		references team(id),
	foreign key(projectid)
		references project(id)
	)

go

create or alter procedure addTeam (@description varchar(100)) as
begin 

	if(@description is null)
	begin
		raiserror('Description cannot be null', 16, 1); 
		return;
	end
	insert into team values(@description);
	exec sp_log_changes 'Added row to team', 'addTeam'
end 

go
create or alter procedure addProject (@name varchar(100)) as
begin 
	
	if (@name is null)
	begin 
		raiserror('Name cannot be null', 16, 1); 
		return;
	end
	
	insert into project values (@name);
	exec sp_log_changes 'Added row to project', 'addProject'
end 


go
create or alter procedure addTakesPartIn (@description varchar(100), @name varchar(100)) as
begin 

	if(@description is null)
	begin
		raiserror('Description cannot be null', 16, 1); 
		return
	end
	if(@name is null)
	begin
		raiserror('Name cannot be null', 16, 1); 
		return;
	end
	
	declare @teamID int, @projectID int;
	set @teamID = (select id from team where description = @description)
	set @projectID = (select id from project where name = @name)
	
	if (@teamID is null or @projectID is null)
    begin
        raiserror('Id not found', 16, 1); 
		return;
    end

	if (exists (select * from takesPartIn where teamid = @teamID and projectid = @projectID))
	begin
		raiserror('Already exists', 16, 1);
		return;
	end
	insert into takesPartIn values (@teamID, @projectID)
	exec sp_log_changes 'Added row to takesPartIn', 'addTakesPartIn'
end 

go
create or alter procedure successfulAddRollback as
begin
    begin tran;
    begin try 
        exec addTeam 'desc1'
        exec addProject 'name1'
        exec addTakesPartIn 'desc1', 'name1'
    end try
    begin catch
        rollback tran;
        return;
    end catch
    commit tran;
end

go 
create or alter procedure failAddRollback as
begin
	begin tran
	begin try 
        exec addTeam 'desc2'
        exec addProject 'name2'
        exec addTakesPartIn 'sth', 'name1'
    end try
	begin catch
		rollback tran
		return
	end catch
	commit tran
end



go 
create or alter procedure successfulPartialRecoveryNoRollback as
begin
	begin try 
        exec addTeam 'desc3' 
    end try
	begin catch
	print ERROR_MESSAGE();
	end catch

	begin try 
        exec addProject 'name3'
    end try
	begin catch
	print ERROR_MESSAGE();
	end catch
	
	begin try
        exec addTakesPartIn 'desc3', 'name3'
	end try
	begin catch
	end catch
end


go 
create or alter procedure failPartialRecoveryNoRollback as
begin
	begin try 
        exec addTeam 'desc4' 
    end try
	begin catch
	print ERROR_MESSAGE();
	end catch

	begin try 
        exec addProject 'name4'
    end try
	begin catch
	print ERROR_MESSAGE();
	end catch
	
	begin try
        exec addTakesPartIn 'does not exist', 'name4'
	end try
	begin catch
	end catch

end


exec successfulAddRollback;
exec failAddRollback;
exec successfulPartialRecoveryNoRollback;
exec failPartialRecoveryNoRollback;

select * from team;
select * from project;
select * from takesPartIn;

delete from team;
delete from project;
delete from takesPartIn;

drop table takesPartIn;
drop table team;
drop table project;

