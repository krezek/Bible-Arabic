DROP TABLE IF EXISTS john_2;
CREATE VIRTUAL TABLE john_2 USING FTS5(chapter, verse, prefix, suffix, body);

.read john_2/john_2_1.sql
