use sakila;


-- Câu 1: Tạo trigger trên bảng payment, mỗi khi thêm, sửa bảng payment sẽ cập nhật 
-- thông tin đó cùng với thông tin là thời gian thêm, sửa vào bảng payment_log (tạo thêm)
drop table if exists `payment_log`;
CREATE TABLE `payment_log` as select * from payment;
drop trigger if exists `update_payment`;
delimiter //
create trigger `update_payment` after update on payment for each row
begin
	if  (old.customer_id != new.customer_id) or
        (old.staff_id != new.staff_id) or
        (old.rental_id != new.rental_id) or
        (old.amount != new.amount) or
        (old.payment_date != new.payment_date)
	then
		update `payment_log`
        set customer_id = new.customer_id,
            staff_id = new.staff_id,
            rental_id = new.rental_id,
            amount = new.amount,
            payment_date = new.payment_date,
            last_update = current_date()
		where payment_id = old.payment_id;
	end if;
end //





-- Câu 2: Thêm vào bảng inventory cột available có kiểu Boolean hoặc tinyint(1) :
-- Tạo trigger trên bảng rental thực hiện công việc sau:
-- • Khi đĩa film đó được thuê, giá trị available được cập nhật thành false
-- • Khi đĩa film đó được trả lại, giá trị available được cập nhật thành true.
alter table `inventory`
drop column `available`;

alter table `inventory` 
add column  `available` boolean after `store_id`;

drop trigger if exists `rental_update`;
create trigger `rental_update` after update on `rental` for each row
begin 
	if new.rental_date is not null and new.return_date is null
    then 
		update `inventory`
        set `available` = false
        where inventory_id = old.inventory_id;
	elseif new.return_date is not null
    then
		update `inventory`
        set `available` = true
        where inventory_id = old.inventory_id;
	end if;
    
end //





-- Câu 3: Hiển thị lệnh tạo view customer_list trong CSDL sakila. Thực hiện truy vấn
-- trên view customer_list. Thử thực hiện một số cập nhật trên view: ví dụ sửa địa
-- chỉ (address), số điện thoại (phone), thành phố (city). Xem có thể sửa được thông tin nào trong các thông tin


-- Tạo view
drop view `customer_list`;
create view  `customer_list` as 
select c.customer_id as `customer_id`,
	   a.address as `address`,
       a.phone as `phone`, 
       ci.city as `city`
from address a
inner join customer c on a.address_id = c.address_id
inner join city ci on ci.city_id = a.city_id;

-- Truy vấn trên view
select * from customer_list;

-- Thực hiện 1 số cập nhật trên view






-- Câu 4: Tạo view actor_list có thêm trường lưu thông tin các film có diễn viên có tham gia (gợi ý sử dụng group_concat)

use sakila;
drop view if exists `artist_list`;
create view `artist_list` as 
select fa.actor_id, concat(a.first_name, ' ', a.last_name) as actor_name, group_concat(title) as films
from film_actor fa
inner join actor a on a.actor_id = fa.actor_id
inner join film f on f.film_id = fa.film_id
group by fa.actor_id;

select * from artist_list;





-- Câu 5: Tham khảo view sales_by_store của CSDL sakila, tạo view sales_by_customer 
-- để hiển thị doanh số theo khách hàng, sắp xếp theo doanh số giảm dần

select * from sales_by_store;

drop view if exists `sales_by_customer`;

create view `sales_by_customer` as
select concat(a.district, ', ', ci.city) as address, concat(c.first_name, ' ', c.last_name) as customer, sum(p.amount) as total_sale
from address a 
inner join customer c on a.address_id = c.address_id
inner join city ci on ci.city_id = a.city_id
inner join payment p on c.customer_id = p.customer_id
group by c.customer_id
order by total_sale desc;

select * from sales_by_customer;








