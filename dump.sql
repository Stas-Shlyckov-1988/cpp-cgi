CREATE DATABASE `test`;

-- test.Staff definition

CREATE TABLE `Staff` (
  `id` int DEFAULT NULL,
  `name` varchar(255) NOT NULL,
  `position` varchar(30) DEFAULT NULL,
  `birthday` date DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

INSERT INTO test.Staff
(id, name, `position`, birthday)
VALUES(1, 'test1', 1, '2024-09-29');

INSERT INTO test.Staff
(id, name, `position`, birthday)
VALUES(2, 'test2', 2, '2024-09-29');

INSERT INTO test.Staff
(id, name, `position`, birthday)
VALUES(3, 'test3', 3, '2024-09-30');

INSERT INTO test.Staff
(id, name, `position`, birthday)
VALUES(4, 'test4', 4, '2024-09-30');

INSERT INTO test.Staff
(id, name, `position`, birthday)
VALUES(5, 'test5', 5, '2024-09-30');