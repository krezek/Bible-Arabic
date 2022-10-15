DROP TABLE IF EXISTS romans;
CREATE VIRTUAL TABLE romans USING FTS5(chapter, verse, prefix, suffix, body);

.read romans/romans_1.sql
.read romans/romans_2.sql
.read romans/romans_3.sql
.read romans/romans_4.sql
.read romans/romans_5.sql
.read romans/romans_6.sql
.read romans/romans_7.sql
.read romans/romans_8.sql
.read romans/romans_9.sql
.read romans/romans_10.sql
.read romans/romans_11.sql
.read romans/romans_12.sql
.read romans/romans_13.sql
.read romans/romans_14.sql
.read romans/romans_15.sql
.read romans/romans_16.sql
