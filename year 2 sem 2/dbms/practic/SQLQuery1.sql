use whatever

create table Userr(
	id int primary key IDENTITY(1,1),
	firstName varchar(56),
	lastName varchar(56),
	dob date
)

create table Channel(
	id int primary key IDENTITY(1,1),
	name varchar(56),
	creation_date date
)

create table Video(
	id int primary key IDENTITY(1,1),
	name varchar(56),
	category varchar(56),
	duration int,
	downloadable bit,
	noLikes int,
	channelid int not null,
	foreign key (channelid) references Channel(id)
)

create table Liked_Video(
	videoid int not null,
	userid int not null,
	foreign key(videoid) references Video(id),
	dateLiked date
)
create table Subscribed_Channel(
	channelid int not null,
	userid int not null,
	foreign key(channelid) references Channel(id),
	dateSubscribed date
)


insert into Userr values('bob', 'johnson', '2003-03-15')
insert into Userr values('alice', 'cutare', '2004-05-23')
insert into Userr values('new', 'user', '2003-01-13')

insert into Channel values('channelName', '2012-09-11')
insert into Channel values('otherChannel', '2012-05-08')

insert into Video values('1name', '1category', 78, 1, 285, 1)
insert into Video values('2name', '2category', 125, 0, 512, 2)

insert into Liked_Video values(1, 3, '2020-01-01')
insert into Liked_Video values(2, 2, '2019-02-08')

insert into Subscribed_Channel values(1, 2, '2012-05-08')
insert into Subscribed_Channel values(2, 3, '2017-12-04')



-- non repeatable read
use whatever
--T1
begin tran
select * from Channel
waitfor delay '00:00:10'
select * from Channel
commit tran

--solution: use REPEATABLE READ as isolation level

--T2
begin tran
update Channel
	set name = 'UPDATED!' where id = 1
commit tran


use whatever

--t1
set transaction isolation level read uncommitted
begin tran
set transaction isolation level read uncommitted
select lastName from Userr where id = 1
waitfor delay '00:00:10'
update Userr set lastName = 'test11' where id = 1
waitfor delay '00:00:05'
select * from Userr
commit tran
rollback tran
commit tran