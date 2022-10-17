DROP TABLE IF EXISTS timothy_1;
CREATE VIRTUAL TABLE timothy_1 USING FTS5(chapter, verse, prefix, suffix, body);

.read timothy_1/timothy_1_1.sql
.read timothy_1/timothy_1_2.sql
.read timothy_1/timothy_1_3.sql
.read timothy_1/timothy_1_4.sql
.read timothy_1/timothy_1_5.sql
.read timothy_1/timothy_1_6.sql
