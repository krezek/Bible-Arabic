DROP TABLE IF EXISTS ecclesiastes;
CREATE VIRTUAL TABLE ecclesiastes USING FTS5(chapter, verse, prefix, suffix, body);

.read ecclesiastes/ecclesiastes_1.sql
.read ecclesiastes/ecclesiastes_2.sql
.read ecclesiastes/ecclesiastes_3.sql
.read ecclesiastes/ecclesiastes_4.sql
.read ecclesiastes/ecclesiastes_5.sql
.read ecclesiastes/ecclesiastes_6.sql
.read ecclesiastes/ecclesiastes_7.sql
.read ecclesiastes/ecclesiastes_8.sql
.read ecclesiastes/ecclesiastes_9.sql
.read ecclesiastes/ecclesiastes_10.sql
.read ecclesiastes/ecclesiastes_11.sql
.read ecclesiastes/ecclesiastes_12.sql
