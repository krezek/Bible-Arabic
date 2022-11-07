DROP TABLE IF EXISTS ruth;
CREATE VIRTUAL TABLE ruth USING FTS5(chapter, verse, prefix, suffix, body);

.read ruth/ruth_1.sql
.read ruth/ruth_2.sql
.read ruth/ruth_3.sql
.read ruth/ruth_4.sql
