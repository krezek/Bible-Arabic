DROP TABLE IF EXISTS nahum;
CREATE VIRTUAL TABLE nahum USING FTS5(chapter, verse, prefix, suffix, body);

.read nahum/nahum_1.sql
.read nahum/nahum_2.sql
.read nahum/nahum_3.sql
