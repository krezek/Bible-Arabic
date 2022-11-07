DROP TABLE IF EXISTS hebrews;
CREATE VIRTUAL TABLE hebrews USING FTS5(chapter, verse, prefix, suffix, body);

.read hebrews/hebrews_1.sql
.read hebrews/hebrews_2.sql
.read hebrews/hebrews_3.sql
.read hebrews/hebrews_4.sql
.read hebrews/hebrews_5.sql
.read hebrews/hebrews_6.sql
.read hebrews/hebrews_7.sql
.read hebrews/hebrews_8.sql
.read hebrews/hebrews_9.sql
.read hebrews/hebrews_10.sql
.read hebrews/hebrews_11.sql
.read hebrews/hebrews_12.sql
.read hebrews/hebrews_13.sql
