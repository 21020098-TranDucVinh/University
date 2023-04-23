use sakila;

-- Câu 1:
-- Tạo index trên first_name và last_name của customer
-- CREATE INDEX customers_index 
-- ON customer(first_name, last_name);

-- Kiểm tra một số truy vấn trên hai trường

explain select * from customer where first_name = "MARY"; -- Có sử dụng index
explain select * from customer where last_name = "S%"; -- Có sử dụng index
explain select * from customer where first_name like "%M%"; -- Không sử dụng index

-- Câu 2:
explain select * from customer where first_name = "N%"; -- Có sử dụng index
explain select * from customer where first_name like "%N%"; -- Không sử dụng index

-- Câu 3:
-- CREATE UNIQUE INDEX unique_idx_customer  
-- ON customer (email);  

-- Thêm dữ liệu vào bảng
-- select * from customer;
-- insert into customer (customer_id, store_id, first_name, last_name, email, address_id, `active`, create_date, last_update)
-- values (1000, 1, 'Ho', 'Xuan Huong', "MARY.SMITH@sakilacustomer.org", 5, 1, '2006-02-14', '2006-02-15');

-- Không thể thêm dữ liệu trùng email vào trong bảng được.


-- Câu 4: 

-- alter table film add index index_des(`description`(255));

explain select * from film where `description` like "teacher%"; -- Có sử dụng index
explain select * from film where `description` like "%teacher%"; -- Không sử dụng index

-- sử dụng fts
ALTER TABLE film ADD FULLTEXT(description);
explain SELECT * 
FROM film 
WHERE MATCH(description) AGAINST("+teacher" in boolean mode);

-- Câu 5: 
-- create index date_idx
-- on rental(rental_date);

-- Kiểm tra
explain select rental_id from rental
where extract(year from rental_date) = 2005 and extract(month from rental_date) = 5; -- Không sử dụng index


-- Câu 6:
-- ALTER TABLE payment ADD INDEX year_idx ((year(payment_date)));
explain select avg(amount) from payment where year(payment_date) = 2005;







