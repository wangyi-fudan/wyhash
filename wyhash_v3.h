/*	Author: Wang Yi <godspeed_china@yeah.net>	*/
#ifndef wyhash_version_3
#define wyhash_version_3
#include <stdint.h>
#include <string.h>
#if defined(_MSC_VER) && defined(_M_X64)
#    include <intrin.h>
#    pragma intrinsic(_umul128)
#endif
const uint64_t _wyp0 = 0xa0761d6478bd642full, _wyp1 = 0xe7037ed1a0b428dbull,
               _wyp2 = 0x8ebc6af09c88c6e3ull, _wyp3 = 0x589965cc75374cc3ull,
               _wyp4 = 0x1d8e4e27c47d124full;
static inline uint64_t _wyrotr(uint64_t v, unsigned k) {
    return (v >> k) | (v << (64 - k));
}
static inline uint64_t _wymum(uint64_t A, uint64_t B) {
#ifdef WYHASH32
    uint64_t hh = (A >> 32) * (B >> 32), hl = (A >> 32) * (unsigned)B,
             lh = (unsigned)A * (B >> 32),
             ll = (uint64_t)(unsigned)A * (unsigned)B;
    return _wyrotr(hl, 32) ^ _wyrotr(lh, 32) ^ hh ^ ll;
#else
#    ifdef __SIZEOF_INT128__
    __uint128_t r = A;
    r *= B;
    return (r >> 64) ^ r;
#    elif defined(_MSC_VER) && defined(_M_X64)
    A = _umul128(A, B, &B);
    return A ^ B;
#    else
    uint64_t ha = A >> 32, hb = B >> 32, la = (uint32_t)A, lb = (uint32_t)B, hi,
             lo;
    uint64_t rh = ha * hb, rm0 = ha * lb, rm1 = hb * la, rl = la * lb,
             t = rl + (rm0 << 32), c = t < rl;
    lo = t + (rm1 << 32);
    c += lo < t;
    hi = rh + (rm0 >> 32) + (rm1 >> 32) + c;
    return hi ^ lo;
#    endif
#endif
}
static inline uint64_t _wyr8(const uint8_t *p) {
    uint64_t v;
    memcpy(&v, p, 8);
    return v;
}
static inline uint64_t _wyr4(const uint8_t *p) {
    uint32_t v;
    memcpy(&v, p, 4);
    return v;
}
static inline uint64_t _wyr3(const uint8_t *p, unsigned k) {
    return (((uint64_t)p[0]) << 16) | (((uint64_t)p[k >> 1]) << 8) | p[k - 1];
}
static inline uint64_t wyhash(const void *key, uint64_t len, uint64_t seed) {
#if defined(__GNUC__) || defined(__INTEL_COMPILER)
    if (__builtin_expect(!len, 0))
#else
    if (!len)
#endif
        return _wymum(_wymum(seed ^ _wyp0, seed ^ _wyp1), _wyp4);
    const uint8_t *p = (const uint8_t *)key;
    if (len < 4)
        return _wymum(_wymum(_wyr3(p, len) ^ seed ^ _wyp0, seed ^ _wyp1),
                      len ^ _wyp4);
    else if (len <= 8)
        return _wymum(
            _wymum(_wyr4(p) ^ seed ^ _wyp0, _wyr4(p + len - 4) ^ seed ^ _wyp1),
            len ^ _wyp4);
    else if (len <= 16)
        return _wymum(
            _wymum(_wyr8(p) ^ seed ^ _wyp0, _wyr8(p + len - 8) ^ seed ^ _wyp1),
            len ^ _wyp4);
    else if (len <= 24)
        return _wymum(
            _wymum(_wyr8(p) ^ seed ^ _wyp0, _wyr8(p + 8) ^ seed ^ _wyp1) ^
                _wymum(_wyr8(p + len - 8) ^ seed ^ _wyp2, seed ^ _wyp3),
            len ^ _wyp4);
    else if (len <= 32)
        return _wymum(
            _wymum(_wyr8(p) ^ seed ^ _wyp0, _wyr8(p + 8) ^ seed ^ _wyp1) ^
                _wymum(_wyr8(p + 16) ^ seed ^ _wyp2,
                       _wyr8(p + len - 8) ^ seed ^ _wyp3),
            len ^ _wyp4);
    uint64_t see1 = seed, i = len;
    if (i >= 256)
        for (; i >= 256; i -= 256, p += 256) {
            seed =
                _wymum(_wyr8(p) ^ seed ^ _wyp0, _wyr8(p + 8) ^ seed ^ _wyp1) ^
                _wymum(_wyr8(p + 16) ^ seed ^ _wyp2,
                       _wyr8(p + 24) ^ seed ^ _wyp3);
            see1 = _wymum(_wyr8(p + 32) ^ see1 ^ _wyp1,
                          _wyr8(p + 40) ^ see1 ^ _wyp2) ^
                   _wymum(_wyr8(p + 48) ^ see1 ^ _wyp3,
                          _wyr8(p + 56) ^ see1 ^ _wyp0);
            seed = _wymum(_wyr8(p + 64) ^ seed ^ _wyp0,
                          _wyr8(p + 72) ^ seed ^ _wyp1) ^
                   _wymum(_wyr8(p + 80) ^ seed ^ _wyp2,
                          _wyr8(p + 88) ^ seed ^ _wyp3);
            see1 = _wymum(_wyr8(p + 96) ^ see1 ^ _wyp1,
                          _wyr8(p + 104) ^ see1 ^ _wyp2) ^
                   _wymum(_wyr8(p + 112) ^ see1 ^ _wyp3,
                          _wyr8(p + 120) ^ see1 ^ _wyp0);
            seed = _wymum(_wyr8(p + 128) ^ seed ^ _wyp0,
                          _wyr8(p + 136) ^ seed ^ _wyp1) ^
                   _wymum(_wyr8(p + 144) ^ seed ^ _wyp2,
                          _wyr8(p + 152) ^ seed ^ _wyp3);
            see1 = _wymum(_wyr8(p + 160) ^ see1 ^ _wyp1,
                          _wyr8(p + 168) ^ see1 ^ _wyp2) ^
                   _wymum(_wyr8(p + 176) ^ see1 ^ _wyp3,
                          _wyr8(p + 184) ^ see1 ^ _wyp0);
            seed = _wymum(_wyr8(p + 192) ^ seed ^ _wyp0,
                          _wyr8(p + 200) ^ seed ^ _wyp1) ^
                   _wymum(_wyr8(p + 208) ^ seed ^ _wyp2,
                          _wyr8(p + 216) ^ seed ^ _wyp3);
            see1 = _wymum(_wyr8(p + 224) ^ see1 ^ _wyp1,
                          _wyr8(p + 232) ^ see1 ^ _wyp2) ^
                   _wymum(_wyr8(p + 240) ^ see1 ^ _wyp3,
                          _wyr8(p + 248) ^ see1 ^ _wyp0);
        }
    for (; i >= 32; i -= 32, p += 32) {
        seed = _wymum(_wyr8(p) ^ seed ^ _wyp0, _wyr8(p + 8) ^ seed ^ _wyp1);
        see1 =
            _wymum(_wyr8(p + 16) ^ see1 ^ _wyp2, _wyr8(p + 24) ^ see1 ^ _wyp3);
    }
    if (!i) {
    } else if (i < 4)
        seed = _wymum(_wyr3(p, i) ^ seed ^ _wyp0, seed ^ _wyp1);
    else if (i <= 8)
        seed = _wymum(_wyr4(p) ^ seed ^ _wyp0, _wyr4(p + i - 4) ^ seed ^ _wyp1);
    else if (i <= 16)
        seed = _wymum(_wyr8(p) ^ seed ^ _wyp0, _wyr8(p + i - 8) ^ seed ^ _wyp1);
    else if (i <= 24) {
        seed = _wymum(_wyr8(p) ^ seed ^ _wyp0, _wyr8(p + 8) ^ seed ^ _wyp1);
        see1 = _wymum(_wyr8(p + i - 8) ^ see1 ^ _wyp2, see1 ^ _wyp3);
    } else {
        seed = _wymum(_wyr8(p) ^ seed ^ _wyp0, _wyr8(p + 8) ^ seed ^ _wyp1);
        see1 = _wymum(_wyr8(p + 16) ^ see1 ^ _wyp2,
                      _wyr8(p + i - 8) ^ see1 ^ _wyp3);
    }
    return _wymum(seed ^ see1, len ^ _wyp4);
}
static inline uint64_t wyhash64(uint64_t A, uint64_t B) {
    return _wymum(_wymum(A ^ _wyp0, B ^ _wyp1), _wyp2);
}
static inline double wy2u01(uint64_t r) {
    const double _wynorm = 1.0 / (1ull << 52);
    return (r >> 11) * _wynorm;
}
static inline float wy2gau(uint64_t r) {
    const float _wynorm1 = 1.0f / (1ull << 15);
    return (((r >> 16) & 0xffff) + ((r >> 32) & 0xffff) + (r >> 48)) *
               _wynorm1 -
           3.0f;
}
static inline uint64_t wyrand(uint64_t *seed) {
    *seed += _wyp0;
    return _wymum(*seed ^ _wyp1, *seed);
}
static uint64_t _wyrand_seed = 0;
#define WYRAND_MAX 0xffffffffffffffffull
static inline void wysrand(uint64_t seed) { _wyrand_seed = seed; }
static inline uint64_t wygrand(void) {
    uint64_t s;
#if defined(_OPENMP)
#    pragma omp atomic capture
#endif
    {
        _wyrand_seed += _wyp0;
        s = _wyrand_seed;
    }
    return _wymum(s ^ _wyp1, s);
}
#ifdef WYSUM
static inline char *wysum(const void *key, uint64_t len, char result[15]) {
    static const char _wyhanzi[] =
        "一乙二十丁厂七卜人入八九几儿了力乃刀又三于干亏士工土才寸下大丈与万上小"
        "口巾山千乞川亿个勺久凡及夕丸么广亡门义之尸弓己已子卫也女飞刃习叉马乡丰"
        "王井开夫天无元专云扎艺木五支厅不太犬区历尤友匹车巨牙屯比互切瓦止少日中"
        "冈贝内水见午牛手毛气升长仁什片仆化仇币仍仅斤爪反介父从今凶分乏公仓月氏"
        "勿欠风丹匀乌凤勾文六方火为斗忆订计户认心尺引丑巴孔队办以允予劝双书幻玉"
        "刊示末未击打巧正扑扒功扔去甘世古节本术可丙左厉右石布龙平灭轧东卡北占业"
        "旧帅归且旦目叶甲申叮电号田由史只央兄叼叫另叨叹四生失禾丘付仗代仙们仪白"
        "仔他斥瓜乎丛令用甩印乐句匆册犯外处冬鸟务包饥主市立闪兰半汁汇头汉宁穴它"
        "讨写让礼训必议讯记永司尼民出辽奶奴加召皮边发孕圣对台矛纠母幼丝式刑动扛"
        "寺吉扣考托老执巩圾扩扫地扬场耳共芒亚芝朽朴机权过臣再协西压厌在有百存而"
        "页匠夸夺灰达列死成夹轨邪划迈毕至此贞师尘尖劣光当早吐吓虫曲团同吊吃因吸"
        "吗屿帆岁回岂刚则肉网年朱先丢舌竹迁乔伟传乒乓休伍伏优伐延件任伤价份华仰"
        "仿伙伪自血向似后行舟全会杀合兆企众爷伞创肌朵杂危旬旨负各名多争色壮冲冰"
        "庄庆亦刘齐交次衣产决充妄闭问闯羊并关米灯州汗污江池汤忙兴宇守宅字安讲军"
        "许论农讽设访寻那迅尽导异孙阵阳收阶阴防奸如妇好她妈戏羽观欢买红纤级约纪"
        "驰巡寿弄麦形进戒吞远违运扶抚坛技坏扰拒找批扯址走抄坝贡攻赤折抓扮抢孝均"
        "抛投坟抗坑坊抖护壳志扭块声把报却劫芽花芹芬苍芳严芦劳克苏杆杠杜材村杏极"
        "李杨求更束豆两丽医辰励否还歼来连步坚旱盯呈时吴助县里呆园旷围呀吨足邮男"
        "困吵串员听吩吹呜吧吼别岗帐财针钉告我乱利秃秀私每兵估体何但伸作伯伶佣低"
        "你住位伴身皂佛近彻役返余希坐谷妥含邻岔肝肚肠龟免狂犹角删条卵岛迎饭饮系"
        "言冻状亩况床库疗应冷这序辛弃冶忘闲间闷判灶灿弟汪沙汽沃泛沟没沈沉怀忧快"
        "完宋宏牢究穷灾良证启评补初社识诉诊词译君灵即层尿尾迟局改张忌际陆阿陈阻"
        "附妙妖妨努忍劲鸡驱纯纱纳纲驳纵纷纸纹纺驴纽奉玩环武青责现表规抹拢拔拣担"
        "坦押抽拐拖拍者顶拆拥抵拘势抱垃拉拦拌幸招坡披拨择抬其取苦若茂苹苗英范直"
        "茄茎茅林枝杯柜析板松枪构杰述枕丧或画卧事刺枣雨卖矿码厕奔奇奋态欧垄妻轰"
        "顷转斩轮软到非叔肯齿些虎虏肾贤尚旺具果味昆国昌畅明易昂典固忠咐呼鸣咏呢"
        "岸岩帖罗帜岭凯败贩购图钓制知垂牧物乖刮秆和季委佳侍供使例版侄侦侧凭侨佩"
        "货依的迫质欣征往爬彼径所舍金命斧爸采受乳贪念贫肤肺肢肿胀朋股肥服胁周昏"
        "鱼兔狐忽狗备饰饱饲变京享店夜庙府底剂郊废净盲放刻育闸闹郑券卷单炒炊炕炎"
        "炉沫浅法泄河沾泪油泊沿泡注泻泳泥沸波泼泽治怖性怕怜怪学宝宗定宜审宙官空"
        "帘实试郎诗肩房诚衬衫视话诞询该详建肃录隶居届刷屈弦承孟孤陕降限妹姑姐姓"
        "始驾参艰线练组细驶织终驻驼绍经贯奏春帮珍玻毒型挂封持项垮挎城挠政赴赵挡"
        "挺括拴拾挑指垫挣挤拼挖按挥挪某甚革荐巷带草茧茶荒茫荡荣故胡南药标枯柄栋"
        "相查柏柳柱柿栏树要咸威歪研砖厘厚砌砍面耐耍牵残殃轻鸦皆背战点临览竖省削"
        "尝是盼眨哄显哑冒映星昨畏趴胃贵界虹虾蚁思蚂虽品咽骂哗咱响哈咬咳哪炭峡罚"
        "贱贴骨钞钟钢钥钩卸缸拜看矩怎牲选适秒香种秋科重复竿段便俩贷顺修保促侮俭"
        "俗俘信皇泉鬼侵追俊盾待律很须叙剑逃食盆胆胜胞胖脉勉狭狮独狡狱狠贸怨急饶"
        "蚀饺饼弯将奖哀亭亮度迹庭疮疯疫疤姿亲音帝施闻阀阁差养美姜叛送类迷前首逆"
        "总炼炸炮烂剃洁洪洒浇浊洞测洗活派洽染济洋洲浑浓津恒恢恰恼恨举觉宣室宫宪"
        "突穿窃客冠语扁袄祖神祝误诱说诵垦退既屋昼费陡眉孩除险院娃姥姨姻娇怒架贺"
        "盈勇怠柔垒绑绒结绕骄绘给络骆绝绞统耕耗艳泰珠班素蚕顽盏匪捞栽捕振载赶起"
        "盐捎捏埋捉捆捐损都哲逝捡换挽热恐壶挨耻耽恭莲莫荷获晋恶真框桂档桐株桥桃"
        "格校核样根索哥速逗栗配翅辱唇夏础破原套逐烈殊顾轿较顿毙致柴桌虑监紧党晒"
        "眠晓鸭晃晌晕蚊哨哭恩唤啊唉罢峰圆贼贿钱钳钻铁铃铅缺氧特牺造乘敌秤租积秧"
        "秩称秘透笔笑笋债借值倚倾倒倘俱倡候俯倍倦健臭射躬息徒徐舰舱般航途拿爹爱"
        "颂翁脆脂胸胳脏胶脑狸狼逢留皱饿恋桨浆衰高席准座脊症病疾疼疲效离唐资凉站"
        "剖竞部旁旅畜阅羞瓶拳粉料益兼烤烘烦烧烛烟递涛浙涝酒涉消浩海涂浴浮流润浪"
        "浸涨烫涌悟悄悔悦害宽家宵宴宾窄容宰案请朗诸读扇袜袖袍被祥课谁调冤谅谈谊"
        "剥恳展剧屑弱陵陶陷陪娱娘通能难预桑绢绣验继球理捧堵描域掩捷排掉堆推掀授"
        "教掏掠培接控探据掘职基著勒黄萌萝菌菜萄菊萍菠营械梦梢梅检梳梯桶救副票戚"
        "爽聋袭盛雪辅辆虚雀堂常匙晨睁眯眼悬野啦晚啄距跃略蛇累唱患唯崖崭崇圈铜铲"
        "银甜梨犁移笨笼笛符第敏做袋悠偿偶偷您售停偏假得衔盘船斜盒鸽悉欲彩领脚脖"
        "脸脱象够猜猪猎猫猛馅馆凑减毫麻痒痕廊康庸鹿盗章竟商族旋望率着盖粘粗粒断"
        "剪兽清添淋淹渠渐混渔淘液淡深婆梁渗情惜惭悼惧惕惊惨惯寇寄宿窑密谋谎祸谜"
        "逮敢屠弹随蛋隆隐婚婶颈绩绪续骑绳维绵绸绿琴斑替款堪搭塔越趁趋超提堤博揭"
        "喜插揪搜煮援裁搁搂搅握揉斯期欺联散惹葬葛董葡敬葱落朝辜葵棒棋植森椅椒棵"
        "棍棉棚棕惠惑逼厨厦硬确雁殖裂雄暂雅辈悲紫辉敞赏掌晴暑最量喷晶喇遇喊景践"
        "跌跑遗蛙蛛蜓喝喂喘喉幅帽赌赔黑铸铺链销锁锄锅锈锋锐短智毯鹅剩稍程稀税筐"
        "等筑策筛筒答筋筝傲傅牌堡集焦傍储奥街";
    uint64_t h = wyhash(key, len, 0);
    memcpy(result + 1, _wyhanzi + (h & 2047) * 3, 3);
    memcpy(result + 4, _wyhanzi + ((h >> 11) & 2047) * 3, 3);
    memcpy(result + 7, _wyhanzi + ((h >> 22) & 2047) * 3, 3);
    memcpy(result + 10, _wyhanzi + ((h >> 33) & 2047) * 3, 3);
    result[0] = 'w';
    result[13] = 'y';
    result[14] = 0;
    return result;
}
#endif
#endif
