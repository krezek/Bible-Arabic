DROP TABLE IF EXISTS john_3;
CREATE VIRTUAL TABLE john_3 USING FTS5(chapter, verse, prefix, suffix, body);

.read john_3/john_3_1.sql
