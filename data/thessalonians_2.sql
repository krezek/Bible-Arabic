DROP TABLE IF EXISTS thessalonians_2;
CREATE VIRTUAL TABLE thessalonians_2 USING FTS5(chapter, verse, prefix, suffix, body);

.read thessalonians_2/thessalonians_2_1.sql
.read thessalonians_2/thessalonians_2_2.sql
.read thessalonians_2/thessalonians_2_3.sql
