DROP TABLE IF EXISTS haggai;
CREATE VIRTUAL TABLE haggai USING FTS5(chapter, verse, prefix, suffix, body);

.read haggai/haggai_1.sql
.read haggai/haggai_2.sql
