DROP TABLE IF EXISTS amos;
CREATE VIRTUAL TABLE amos USING FTS5(chapter, verse, prefix, suffix, body);

.read amos/amos_1.sql
.read amos/amos_2.sql
.read amos/amos_3.sql
.read amos/amos_4.sql
.read amos/amos_5.sql
.read amos/amos_6.sql
.read amos/amos_7.sql
.read amos/amos_8.sql
.read amos/amos_9.sql
