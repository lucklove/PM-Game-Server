#
# Encoding: Unicode (UTF-8)
#


DROP TABLE IF EXISTS `ability`;
DROP TABLE IF EXISTS `level`;
DROP TABLE IF EXISTS `monster`;
DROP TABLE IF EXISTS `pm`;
DROP TABLE IF EXISTS `skill`;
DROP TABLE IF EXISTS `type`;


CREATE TABLE `ability` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(128) DEFAULT NULL,
  `prompt` text,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=124 DEFAULT CHARSET=utf8;


CREATE TABLE `level` (
  `id` int(8) NOT NULL AUTO_INCREMENT,
  `target_level` int(8) NOT NULL DEFAULT '0',
  `exp_required` int(8) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=101 DEFAULT CHARSET=utf8;


CREATE TABLE `monster` (
  `id` int(8) NOT NULL AUTO_INCREMENT,
  `name` varchar(128) NOT NULL DEFAULT '',
  `level` int(8) NOT NULL DEFAULT '0',
  `exp` int(8) NOT NULL DEFAULT '0',
  `type` int(8) NOT NULL DEFAULT '0',
  `bs_hp` int(8) NOT NULL DEFAULT '0',
  `bs_atk` int(8) NOT NULL DEFAULT '0',
  `bs_def` int(8) NOT NULL DEFAULT '0',
  `bs_satk` int(8) NOT NULL DEFAULT '0',
  `bs_sdef` int(8) NOT NULL DEFAULT '0',
  `bs_spd` int(8) NOT NULL DEFAULT '0',
  `ev_hp` int(8) NOT NULL DEFAULT '0',
  `ev_htk` int(8) NOT NULL DEFAULT '0',
  `ev_def` int(8) NOT NULL DEFAULT '0',
  `ev_satk` int(8) NOT NULL DEFAULT '0',
  `ev_sdef` int(8) NOT NULL DEFAULT '0',
  `ev_spd` int(8) NOT NULL DEFAULT '0',
  `atk_lv` int(8) NOT NULL DEFAULT '0',
  `def_lv` int(8) NOT NULL DEFAULT '0',
  `satk_lv` int(8) NOT NULL DEFAULT '0',
  `sdef_lv` int(8) NOT NULL DEFAULT '0',
  `spd_lv` int(8) NOT NULL DEFAULT '0',
  `acc_lv` int(8) NOT NULL DEFAULT '0',
  `crit_lv` int(8) NOT NULL DEFAULT '0',
  `skill1` int(8) NOT NULL DEFAULT '0',
  `skill2` int(8) NOT NULL DEFAULT '0',
  `skill3` int(8) NOT NULL DEFAULT '0',
  `skill4` int(8) NOT NULL DEFAULT '0',
  `ability` int(8) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE `pm` (
  `id` int(8) NOT NULL DEFAULT '0',
  `base_name` varchar(128) NOT NULL DEFAULT '',
  `base_type` int(8) NOT NULL DEFAULT '0',
  `base_ability_enable` int(8) NOT NULL DEFAULT '0',
  `base_born_ability` int(8) NOT NULL DEFAULT '0',
  `base_stat_hp` int(8) NOT NULL DEFAULT '0',
  `base_stat_atk` int(8) NOT NULL DEFAULT '0',
  `base_stat_def` int(8) NOT NULL DEFAULT '0',
  `base_stat_satk` int(8) NOT NULL DEFAULT '0',
  `base_stat_sdef` int(8) NOT NULL DEFAULT '0',
  `base_stat_spd` int(8) NOT NULL DEFAULT '0',
  `base_skill_enable` int(8) NOT NULL DEFAULT '0',
  `base_born_skill` int(8) NOT NULL DEFAULT '0',
  `base_catch_rate` int(8) NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE `skill` (
  `id` int(8) NOT NULL AUTO_INCREMENT,
  `name` varchar(128) NOT NULL DEFAULT '',
  `type` int(8) NOT NULL DEFAULT '0',
  `class` int(8) NOT NULL DEFAULT '0',
  `power` int(8) NOT NULL DEFAULT '0',
  `acc` int(8) NOT NULL DEFAULT '0',
  `is_melee` int(8) NOT NULL DEFAULT '0',
  `damage_hurt` int(8) NOT NULL DEFAULT '0',
  `weather_eff` int(8) NOT NULL DEFAULT '0',
  `rate_attr` int(8) NOT NULL DEFAULT '0',
  `attr` int(8) NOT NULL DEFAULT '0',
  `lvl_attr` int(8) NOT NULL DEFAULT '0',
  `rate_debuff` int(8) NOT NULL DEFAULT '0',
  `debuff` int(8) NOT NULL DEFAULT '0',
  `rate_cond` int(8) NOT NULL DEFAULT '0',
  `cond` int(8) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=160 DEFAULT CHARSET=utf8;


CREATE TABLE `type` (
  `id` int(11) DEFAULT NULL,
  `name` varchar(128) DEFAULT NULL,
  `atk_good` varchar(128) DEFAULT NULL,
  `atk_bad` varchar(128) DEFAULT NULL,
  `atk_immune` varchar(128) DEFAULT NULL,
  `def_good` varchar(128) DEFAULT NULL,
  `def_bad` varchar(128) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;




SET FOREIGN_KEY_CHECKS = 0;


LOCK TABLES `ability` WRITE;
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (1, '恶臭', '造成技能伤害时10%概率令对手害怕');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (2, '降雨', '在战斗中出场时天气变为下雨');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (3, '加速', '在战斗中每回合结束时速度上升一级');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (4, '战斗盔甲', '不会被对方的攻击击中要害');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (5, '坚硬', '不会受到一击必杀技的效果，此外，HP全满时即使受到一击致命攻击，也能留下最后的体力');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (6, '潮湿', '出战中，自爆与大爆炸技能不能使用，并且引爆特性也不会发动');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (7, '柔软', '在战斗中不会被麻痹');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (8, '沙隐', '天气为沙暴时，回避率加倍，并且不会受到沙暴伤害');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (9, '静电', '受到接触攻击时，有几率令攻击方麻痹');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (10, '蓄电', '使电系技能伤害无效，同时回复体力');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (11, '贮水', '使水系技能伤害无效，同时回复体力');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (12, '钝感', '战斗中不会被魅惑');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (13, '无天气', '出战后，禁用天气效果，天气恢复为正常');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (14, '复眼', '技能命中率提高，效果为1.5倍');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (15, '不眠', '战斗中不会睡眠');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (16, '变色', '受到对方的技能时，自己的属性变为与所受技能属性相同');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (17, '免疫', '战斗中不会中毒');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (18, '引火', '受到的火系技能无效化，同时自己的火系技能伤害提高30%');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (19, '鳞粉', '不会受到对方技能的追加效果（能力变化与BUFF类效果）');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (20, '自我中心', '战斗中不会混乱');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (21, '吸盘', '无效化能把对手吹飞的技能排在队伍首位时，容易用钓竿钓起精灵');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (22, '威吓', '在战斗中出场时，降低对方精灵的普攻能力1级');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (23, '踩影', '令对方的精灵不能逃跑，并且不能交换');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (24, '鲨鱼皮', '受到近程攻击时，对攻击方造成其最大生命值1/8的伤害');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (25, '奇异守护', '除了效果显著的技能外，不会受到技能伤害');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (26, '浮游', '不会受到地面系的技能伤害');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (27, '孢子', '受到接触攻击时，有30%概率令攻击方中毒、麻痹或睡眠之一');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (28, '同步率', '被施加中毒、麻痹或烧伤时，令对方处于相同状态');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (29, '净体', '能力不会被对方的技能或特性降低');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (30, '自然回复', '从战斗中退场时，能治好异常状态');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (31, '避雷针', '受到的电系技能无效化，同时自己的特攻能力提高1级');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (32, '天之恩惠', '攻击技能的追加效果概率翻倍');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (33, '轻快', '天气为雨天时，速度提升2级');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (34, '叶绿素', '阳光强烈时，速度提升2级');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (35, '发光', '排在队伍首位时，遇到精灵的概率翻倍');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (36, '复制', '在战斗中出场时，特性变为与对手一样');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (37, '大力士', '所有技能威力翻倍');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (38, '毒刺', '受到近程攻击时，有30%概率令攻击方中毒');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (39, '精神力', '不会害怕');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (40, '熔岩铠甲', '不会冰冻');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (41, '水之掩护', '不会烧伤');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (42, '磁力', '令对方的精灵不能逃跑，并且不能交换');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (43, '防音', '令用声音攻击的技能无效，对来自己方的技能也会无效化');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (44, '接雨盘', '天气为雨天时，每回合回复最大生命的1/16');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (45, '起沙', '在战斗中出场时天气变为沙暴');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (46, '压力', '令对方序号为1的技能释放顺序与序号为4的技能调换');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (47, '厚脂肪', '受到火与冰系技能伤害减半');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (48, '早起', '睡眠状态持续回合数减半');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (49, '火焰之躯', '受到近程攻击时，有30&概率令攻击方烧伤');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (50, '逃足', '在与野生精灵战斗中必定能逃跑可以无视禁止对方逃跑的技能或特性效果');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (51, '锐利目光', '战斗中命中率不会被降低');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (52, '怪力钳', '战斗中攻击不会被降低');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (53, '拾取', '冒险过程中，获得道具的概率增加为1.5倍');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (54, '懒惰', '2回合内只能行动1次');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (55, '紧张', '攻击提高，相对的，命中率降低');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (56, '魅惑身躯', '受到接触攻击时，有几率令攻击方着迷排在队伍首位时，容易遇到性别不同的精灵');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (57, '正极', '与正极或负极特性的精灵一起参加战斗时，特攻提高');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (58, '负极', '与正极或负极特性的精灵一起参加战斗时，特攻提高');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (59, '气象台', '这个特性的漂浮泡泡能随着天气改变属性');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (60, '黏着', '携带的道具不会被夺走');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (61, '蜕皮', '每回合结束后有1/3概率回复异常状态');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (62, '根性', '处于异常状态时攻击提高至1.5倍，该效果能使烧伤的攻击减半无效');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (63, '神秘鳞片', '处于异常状态时防御提高至1.5倍');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (64, '毒疗', '中毒时不会减血，生命反而会增加');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (65, '深绿', '生命低于上限的1/3时，草系技能的威力提高1.5倍');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (66, '猛火', '生命低于上限的1/3时，火系技能的威力提高1.5倍');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (67, '激流', '生命低于上限的1/3时，水系技能的威力提高1.5倍');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (68, '虫之预感', '生命低于上限的1/3时，虫系技能的威力提高1.5倍');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (69, '石脑', '即使使用反作用力技能也不会受到反作用伤害');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (70, '干旱', '在战斗中出场时，阳光变得强烈');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (71, '蚁地狱', '令飞行属性或浮游特性之外的精灵不能逃跑与交换，但可以通过技能效果交换');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (72, '干劲', '战斗中不会睡眠');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (73, '白烟', '能力等级不会被对方的技能或特性降低');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (74, '瑜珈之力', '所有技能威力翻倍');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (75, '贝壳盔甲', '免疫暴击');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (76, '天气锁', '出战后，禁用天气效果，天气恢复为正常');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (77, '蹒跚', '混乱状态下回避率提高20%');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (78, '电引擎', '使受到的电系技能伤害无效化，同时自己的速度提升1级');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (79, '斗争心', '对属性（多属性只要一种）相同的敌人，技能威力提高为1.25倍');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (80, '不屈之心', '害怕时，速度提高1级');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (81, '雪隐', '天气为冰雹时，回避率提高20%');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (82, '吃货', '使用努力值提升类消耗品时，效果翻倍');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (83, '怒穴', '受到暴击时，攻击等级提升至6级');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (84, '轻身', '生命低于上限的1/3时，速度提升2级');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (85, '耐热', '受到的火系技能伤害减半，但对烧伤伤害无效');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (86, '单纯', '能力等级变化的效果翻倍');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (87, '干燥肌肤', '受到水系技能时回复最大生命1/4，受到火系技能时对方威力提升至1.25倍');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (88, '下载', '若对方的防御＜特防，自己的攻击提升1级；若对方的防御≥特防，自己的特攻提升1级');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (89, '铁拳', '用近程攻击的技能威力提高1.2倍');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (90, '毒疗', '中毒时每回合逐渐回复体力');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (91, '适应力', '使用与自己属性相同的技能时，伤害倍率增加至2倍');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (92, '技能连锁', '使用连续攻击技时，攻击次数必定最大');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (93, '湿润身躯', '天气为雨天时，不进会处于异常状态');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (94, '太阳力量', '阳光强烈时，特攻提高2级');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (95, '早足', '处于异常状态时，速度提高1级，并且麻痹的速度降低效果无效');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (96, '普通皮肤', '所有技能全部变为普通属性');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (97, '狙击手', '攻击暴击时，暴击伤害额外提高50%');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (98, '魔法守护', '不会受到天气与异常状态造成的伤害');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (99, '无防御', '在战斗中，双方攻击必定能命中');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (100, '后出', '无视速度必定后攻');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (101, '技师', '技能威力小于或等于60的，威力提升50%');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (102, '绿叶守护', '阳光强烈时不会处于异常状态');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (103, '不器用', '不会发动携带道具的效果');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (104, '破格', '禁用对方特性');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (105, '强运', '技能容易击中要害');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (106, '引爆', '受到近程攻击濒死时，对对方造成其最大生命1/4的伤害。');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (107, '危险预知', '如果对方拥有对自己效果显著的技能时会战栗地说明对于一击必杀技与自爆、大爆炸也会说明');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (108, '预知梦', '对方非必中的命中率降低10%');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (109, '天然', '除速度外，自己的能力等级变化无效');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (110, '有色眼镜', '使用非属性相克的技能时，造成的伤害翻倍');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (111, '过滤器', '受到对方属性相克的技能时，伤害减半');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (112, '缓慢启动', '进入战斗的5回合之内攻击与速度降低至一半');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (113, '胆气', '普通属性与格斗属性的技能能击中幽灵属性的精灵');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (114, '引水', '受到的水系技能无效化，自己的特攻提高1级');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (115, '寒冰身躯', '天气为冰雹时，每回合回复最大生命1/16');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (116, '坚岩', '受到对方属性相克的技能时，伤害减半');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (117, '降雪', '进入战斗时天气变为冰雹');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (118, '集蜜', '战斗结束时，偶尔能捡到甜蜜，精灵等级越高越容易捡到');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (119, '洞察', '如果对方携带道具，会说明携带的道具');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (120, '舍身', '使用有反伤的技能攻击时，技能威力提高至1.2倍');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (121, '多重属性', '这个特性的阿尔宙斯携带石板时，会根据不同的石板变成对应的属性');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (122, '花之礼物', '在阳光强烈时特防能力提高2级');
INSERT INTO `ability` (`id`, `name`, `prompt`) VALUES (123, '梦魇', '每回合减少睡眠状态的对手的体力');
UNLOCK TABLES;


LOCK TABLES `level` WRITE;
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (1, 1, 0);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (2, 2, 4);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (3, 3, 13);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (4, 4, 32);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (5, 5, 65);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (6, 6, 113);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (7, 7, 182);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (8, 8, 276);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (9, 9, 398);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (10, 10, 553);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (11, 11, 745);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (12, 12, 979);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (13, 13, 1259);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (14, 14, 1591);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (15, 15, 1980);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (16, 16, 2457);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (17, 17, 3046);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (18, 18, 3732);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (19, 19, 4526);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (20, 20, 5440);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (21, 21, 6482);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (22, 22, 7666);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (23, 23, 9003);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (24, 24, 10506);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (25, 25, 12187);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (26, 26, 14060);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (27, 27, 16140);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (28, 28, 18439);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (29, 29, 20974);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (30, 30, 23760);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (31, 31, 26811);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (32, 32, 30146);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (33, 33, 33780);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (34, 34, 37731);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (35, 35, 42017);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (36, 36, 46656);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (37, 37, 50653);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (38, 38, 55969);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (39, 39, 60505);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (40, 40, 66560);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (41, 41, 71677);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (42, 42, 78533);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (43, 43, 84277);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (44, 44, 91998);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (45, 45, 98415);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (46, 46, 107069);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (47, 47, 114205);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (48, 48, 123863);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (49, 49, 131766);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (50, 50, 142500);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (51, 51, 151222);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (52, 52, 163105);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (53, 53, 172697);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (54, 54, 185807);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (55, 55, 196322);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (56, 56, 210739);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (57, 57, 222231);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (58, 58, 238036);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (59, 59, 250562);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (60, 60, 267840);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (61, 61, 281456);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (62, 62, 300293);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (63, 63, 315059);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (64, 64, 335544);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (65, 65, 351520);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (66, 66, 373744);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (67, 67, 390991);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (68, 68, 415050);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (69, 69, 433631);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (70, 70, 459620);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (71, 71, 479600);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (72, 72, 507617);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (73, 73, 529063);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (74, 74, 559209);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (75, 75, 582187);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (76, 76, 614566);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (77, 77, 639146);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (78, 78, 673863);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (79, 79, 700115);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (80, 80, 737280);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (81, 81, 765275);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (82, 82, 804997);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (83, 83, 834809);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (84, 84, 877201);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (85, 85, 908905);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (86, 86, 954084);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (87, 87, 987754);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (88, 88, 1035837);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (89, 89, 1071552);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (90, 90, 1122660);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (91, 91, 1160499);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (92, 92, 1214753);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (93, 93, 1254796);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (94, 94, 1312322);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (95, 95, 1354652);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (96, 96, 1415577);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (97, 97, 1460276);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (98, 98, 1524731);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (99, 99, 1571884);
INSERT INTO `level` (`id`, `target_level`, `exp_required`) VALUES (100, 100, 1640000);
UNLOCK TABLES;


LOCK TABLES `monster` WRITE;
UNLOCK TABLES;


LOCK TABLES `pm` WRITE;
UNLOCK TABLES;


LOCK TABLES `skill` WRITE;
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (1, '拍击', 1, 1, 40, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (2, '手刀', 7, 1, 50, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (3, '连环巴掌', 1, 1, 15, 85, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (4, '连续拳', 1, 1, 18, 85, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (5, '百万吨拳击', 1, 1, 80, 85, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (6, '聚宝功', 1, 1, 40, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (7, '火焰拳', 2, 1, 75, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (8, '急冻拳', 6, 1, 75, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (9, '雷光掌', 5, 1, 75, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (10, '利爪', 1, 1, 40, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (11, '剪断', 1, 1, 55, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (12, '剪刀断头台', 1, 1, 250, 30, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (13, '旋风刀', 1, 2, 80, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (14, '剑舞', 1, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (15, '一字斩', 1, 1, 50, 95, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (16, '烈暴风', 10, 2, 40, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (17, '翅膀攻击', 10, 1, 60, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (18, '旋风', 1, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (19, '飞翔', 10, 1, 90, 95, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (20, '绑紧', 1, 1, 15, 85, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (21, '叩打', 1, 1, 80, 75, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (22, '藤鞭', 4, 1, 45, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (23, '践踏', 1, 1, 65, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (24, '连环腿', 7, 1, 30, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (25, '百万吨飞腿', 1, 1, 120, 75, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (26, '飞踢', 7, 1, 100, 95, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (27, '旋风腿', 7, 1, 60, 85, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (28, '飞沙脚', 9, 0, 0, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (29, '铁头功', 1, 1, 70, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (30, '角撞', 1, 1, 65, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (31, '疯狂攻击', 1, 1, 15, 85, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (32, '独角钻', 1, 1, 120, 50, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (33, '冲击', 1, 1, 50, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (34, '泰山压顶', 1, 1, 85, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (35, '捆绑', 1, 1, 15, 90, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (36, '猛撞', 1, 1, 90, 85, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (37, '横冲直撞', 1, 1, 120, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (38, '舍身攻击', 1, 1, 120, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (39, '摇尾巴', 1, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (40, '毒针', 8, 1, 15, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (41, '双针', 12, 1, 25, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (42, '飞弹针', 12, 1, 25, 95, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (43, '瞪眼', 1, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (44, '咬咬', 16, 1, 60, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (45, '嚎叫', 1, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (46, '吼叫', 1, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (47, '唱歌', 1, 0, 0, 55, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (48, '超音波', 1, 0, 0, 55, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (49, '音爆', 1, 2, 80, 90, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (50, '石化功', 1, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (51, '溶解液', 8, 2, 40, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (52, '火花', 2, 2, 40, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (53, '喷射火焰', 2, 2, 90, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (54, '白雾', 6, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (55, '水枪', 3, 2, 40, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (56, '水炮', 3, 2, 110, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (57, '冲浪', 3, 2, 90, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (58, '急冻光线', 6, 2, 90, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (59, '暴风雪', 6, 2, 110, 70, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (60, '幻象光', 11, 2, 65, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (61, '泡沫光线', 3, 2, 65, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (62, '极光束', 6, 2, 65, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (63, '破坏死光', 1, 2, 150, 90, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (64, '啄', 10, 1, 35, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (65, '冲钻', 10, 1, 80, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (66, '地狱滚动', 7, 1, 80, 80, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (67, '下踢', 7, 1, 50, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (68, '返拳', 7, 1, 75, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (69, '地球上投', 7, 1, 60, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (70, '劲力', 1, 1, 80, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (71, '吸收', 4, 2, 20, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (72, '百万吨吸收', 4, 2, 40, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (73, '寄生种子', 4, 0, 0, 90, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (74, '生长', 1, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (75, '飞叶快刀', 4, 1, 55, 95, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (76, '阳光烈焰', 4, 2, 120, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (77, '毒粉末', 8, 0, 0, 75, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (78, '麻痹粉', 4, 0, 0, 75, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (79, '睡眠粉', 4, 0, 0, 75, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (80, '花之舞', 4, 2, 120, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (81, '吐丝', 12, 0, 0, 95, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (82, '龙之怒', 15, 2, 60, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (83, '火焰漩涡', 2, 2, 35, 85, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (84, '电击', 5, 2, 40, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (85, '十万伏特', 5, 2, 90, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (86, '电磁波', 5, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (87, '打雷', 5, 2, 110, 70, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (88, '滚石', 13, 1, 50, 90, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (89, '地震', 9, 1, 100, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (90, '地裂', 9, 1, 250, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (91, '挖地洞', 9, 1, 80, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (92, '猛毒素', 8, 0, 0, 90, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (93, '念力', 11, 2, 50, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (94, '幻象术', 11, 2, 90, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (95, '催眠术', 11, 0, 0, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (96, '瑜伽姿势', 11, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (97, '高速移动', 11, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (98, '电光一闪', 1, 1, 40, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (99, '愤怒', 1, 1, 20, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (100, '瞬间移动', 11, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (101, '黑夜诅咒', 14, 2, 50, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (102, '模仿', 1, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (103, '噪音', 1, 0, 0, 85, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (104, '影子分身', 1, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (105, '自我复原', 1, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (106, '硬梆梆', 1, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (107, '缩小', 1, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (108, '烟幕', 1, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (109, '奇异光线', 14, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (110, '缩壳', 3, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (111, '防卫卷', 1, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (112, '障碍', 11, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (113, '光墙', 11, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (114, '黑雾', 6, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (115, '减半反射', 11, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (116, '集气', 1, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (117, '忍忍', 1, 1, 100, 90, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (118, '炸蛋', 1, 1, 100, 75, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (119, '舔舌头', 14, 1, 30, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (120, '迷雾', 8, 2, 30, 70, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (121, '泥浆攻击', 8, 2, 65, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (122, '骨棒', 9, 1, 65, 85, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (123, '大字爆', 2, 2, 110, 85, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (124, '鱼跃龙门', 3, 1, 80, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (125, '夹壳', 3, 1, 35, 85, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (126, '高速星星', 1, 2, 60, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (127, '火箭头槌', 1, 1, 130, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (128, '尖刺加农炮', 1, 1, 20, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (129, '纠缠', 1, 1, 10, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (130, '瞬间失忆', 11, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (131, '折弯汤匙', 11, 0, 0, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (132, '生蛋', 1, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (133, '飞膝撞', 7, 1, 130, 90, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (134, '大蛇瞪眼', 1, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (135, '毒瓦斯', 8, 0, 0, 90, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (136, '丢球', 1, 1, 15, 85, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (137, '吸血', 12, 1, 20, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (138, '恶魔之吻', 1, 0, 0, 7500, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (139, '高空攻击', 10, 1, 140, 90, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (140, '变身', 1, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (141, '泡泡', 3, 2, 40, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (142, '迷昏拳', 1, 1, 70, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (143, '蘑菇孢子', 4, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (144, '闪光', 1, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (145, '幻象波', 11, 2, 50, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (146, '水溅跃', 1, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (147, '溶化', 8, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (148, '螃蟹拳', 3, 1, 100, 90, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (149, '疯狂乱抓', 1, 1, 18, 80, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (150, '骨头回力镖', 9, 1, 50, 90, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (151, '睡觉', 11, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (152, '山崩地裂', 13, 1, 75, 90, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (153, '必杀门牙', 1, 1, 80, 90, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (154, '棱角', 1, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (155, '三角攻击', 1, 2, 80, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (156, '愤怒之牙', 1, 1, 110, 90, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (157, '劈开', 1, 1, 70, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (158, '替身', 1, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `skill` (`id`, `name`, `type`, `class`, `power`, `acc`, `is_melee`, `damage_hurt`, `weather_eff`, `rate_attr`, `attr`, `lvl_attr`, `rate_debuff`, `debuff`, `rate_cond`, `cond`) VALUES (159, '挣扎', 1, 1, 50, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
UNLOCK TABLES;


LOCK TABLES `type` WRITE;
UNLOCK TABLES;




SET FOREIGN_KEY_CHECKS = 1;


