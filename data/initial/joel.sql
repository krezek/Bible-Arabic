DROP TABLE IF EXISTS joel;
CREATE VIRTUAL TABLE joel USING FTS5(chapter, verse, prefix, suffix, body);

.read joel/joel_1.sql
.read joel/joel_2.sql
.read joel/joel_3.sql
