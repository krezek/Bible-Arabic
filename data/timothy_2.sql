DROP TABLE IF EXISTS timothy_2;
CREATE VIRTUAL TABLE timothy_2 USING FTS5(chapter, verse, prefix, suffix, body);

.read timothy_2/timothy_2_1.sql
.read timothy_2/timothy_2_2.sql
.read timothy_2/timothy_2_3.sql
.read timothy_2/timothy_2_4.sql
