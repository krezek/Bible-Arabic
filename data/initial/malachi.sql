DROP TABLE IF EXISTS malachi;
CREATE VIRTUAL TABLE malachi USING FTS5(chapter, verse, prefix, suffix, body);

.read malachi/malachi_1.sql
.read malachi/malachi_2.sql
.read malachi/malachi_3.sql
.read malachi/malachi_4.sql
