DROP TABLE IF EXISTS daniel;
CREATE VIRTUAL TABLE daniel USING FTS5(chapter, verse, prefix, suffix, body);

.read daniel/daniel_1.sql
.read daniel/daniel_2.sql
.read daniel/daniel_3.sql
.read daniel/daniel_4.sql
.read daniel/daniel_5.sql
.read daniel/daniel_6.sql
.read daniel/daniel_7.sql
.read daniel/daniel_8.sql
.read daniel/daniel_9.sql
.read daniel/daniel_10.sql
.read daniel/daniel_11.sql
.read daniel/daniel_12.sql
