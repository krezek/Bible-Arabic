DROP TABLE IF EXISTS titus;
CREATE VIRTUAL TABLE titus USING FTS5(chapter, verse, prefix, suffix, body);

.read titus/titus_1.sql
.read titus/titus_2.sql
.read titus/titus_3.sql
