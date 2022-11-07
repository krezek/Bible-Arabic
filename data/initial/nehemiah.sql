DROP TABLE IF EXISTS nehemiah;
CREATE VIRTUAL TABLE nehemiah USING FTS5(chapter, verse, prefix, suffix, body);

.read nehemiah/nehemiah_1.sql
.read nehemiah/nehemiah_2.sql
.read nehemiah/nehemiah_3.sql
.read nehemiah/nehemiah_4.sql
.read nehemiah/nehemiah_5.sql
.read nehemiah/nehemiah_6.sql
.read nehemiah/nehemiah_7.sql
.read nehemiah/nehemiah_8.sql
.read nehemiah/nehemiah_9.sql
.read nehemiah/nehemiah_10.sql
.read nehemiah/nehemiah_11.sql
.read nehemiah/nehemiah_12.sql
.read nehemiah/nehemiah_13.sql
