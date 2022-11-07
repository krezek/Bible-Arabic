DROP TABLE IF EXISTS john_1;
CREATE VIRTUAL TABLE john_1 USING FTS5(chapter, verse, prefix, suffix, body);

.read john_1/john_1_1.sql
.read john_1/john_1_2.sql
.read john_1/john_1_3.sql
.read john_1/john_1_4.sql
.read john_1/john_1_5.sql
