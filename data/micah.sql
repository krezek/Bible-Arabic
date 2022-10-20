DROP TABLE IF EXISTS micah;
CREATE VIRTUAL TABLE micah USING FTS5(chapter, verse, prefix, suffix, body);

.read micah/micah_1.sql
.read micah/micah_2.sql
.read micah/micah_3.sql
.read micah/micah_4.sql
.read micah/micah_5.sql
.read micah/micah_6.sql
.read micah/micah_7.sql
