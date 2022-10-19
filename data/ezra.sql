DROP TABLE IF EXISTS ezra;
CREATE VIRTUAL TABLE ezra USING FTS5(chapter, verse, prefix, suffix, body);

.read ezra/ezra_1.sql
.read ezra/ezra_2.sql
.read ezra/ezra_3.sql
.read ezra/ezra_4.sql
.read ezra/ezra_5.sql
.read ezra/ezra_6.sql
.read ezra/ezra_7.sql
.read ezra/ezra_8.sql
.read ezra/ezra_9.sql
.read ezra/ezra_10.sql
