DROP TABLE IF EXISTS esther;
CREATE VIRTUAL TABLE esther USING FTS5(chapter, verse, prefix, suffix, body);

.read esther/esther_1.sql
.read esther/esther_2.sql
.read esther/esther_3.sql
.read esther/esther_4.sql
.read esther/esther_5.sql
.read esther/esther_6.sql
.read esther/esther_7.sql
.read esther/esther_8.sql
.read esther/esther_9.sql
.read esther/esther_10.sql
