DROP TABLE IF EXISTS james;
CREATE VIRTUAL TABLE james USING FTS5(chapter, verse, prefix, suffix, body);

.read james/james_1.sql
.read james/james_2.sql
.read james/james_3.sql
.read james/james_4.sql
.read james/james_5.sql
