DROP TABLE IF EXISTS genesis;
CREATE VIRTUAL TABLE genesis USING FTS5(chapter, verse, prefix, suffix, body);


INSERT INTO genesis (chapter, verse, prefix, suffix, body)
VALUES (1, 1, NULL, NULL, "فِي الْبَدْءِ خَلَقَ اللهُ السَّمَاوَاتِ وَالأَرْضَ.");

INSERT INTO genesis (chapter, verse, prefix, suffix, body)
VALUES (1, 2, NULL, NULL, "وَكَانَتِ الأَرْضُ خَرِبَةً وَخَالِيَةً، وَعَلَى وَجْهِ الْغَمْرِ ظُلْمَةٌ، وَرُوحُ اللهِ يَرِفُّ عَلَى وَجْهِ الْمِيَاهِ.");

INSERT INTO genesis (chapter, verse, prefix, suffix, body)
VALUES (1, 3, NULL, NULL, "وَقَالَ اللهُ: «لِيَكُنْ نُورٌ»، فَكَانَ نُورٌ.");



INSERT INTO genesis (chapter, verse, prefix, suffix, body)
VALUES (2, 1, NULL, NULL, "فَأُكْمِلَتِ السَّمَاوَاتُ وَالأَرْضُ وَكُلُّ جُنْدِهَا.");

INSERT INTO genesis (chapter, verse, prefix, suffix, body)
VALUES (2, 2, NULL, NULL, "وَفَرَغَ اللهُ فِي الْيَوْمِ السَّابعِ مِنْ عَمَلِهِ الَّذِي عَمِلَ. فَاسْتَرَاحَ فِي الْيَوْمِ السَّابعِ مِنْ جَمِيعِ عَمَلِهِ الَّذِي عَمِلَ.");

INSERT INTO genesis (chapter, verse, prefix, suffix, body)
VALUES (2, 3, NULL, NULL, "وَبَارَكَ اللهُ الْيَوْمَ السَّابعَ وَقَدَّسَهُ، لأَنَّهُ فِيهِ اسْتَرَاحَ مِنْ جَمِيعِ عَمَلِهِ الَّذِي عَمِلَ اللهُ خَالِقًا.");
