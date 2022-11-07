DROP TABLE IF EXISTS lamentations;
CREATE VIRTUAL TABLE lamentations USING FTS5(chapter, verse, prefix, suffix, body);

.read lamentations/lamentations_1.sql
.read lamentations/lamentations_2.sql
.read lamentations/lamentations_3.sql
.read lamentations/lamentations_4.sql
.read lamentations/lamentations_5.sql
