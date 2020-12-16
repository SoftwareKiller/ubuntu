#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>

using namespace std;

//好吧，暴力终将被制裁
vector<vector<string>> groupAnagrams_(vector<string>& strs)
{
    map<string, multiset<char>> filter;
    for(int i = 0; i < strs.size(); ++i)
    {
        multiset<char> s;
        for(int j = 0; j < strs[i].length(); ++j)
        {
            s.insert(strs[i][j]);
        }
        filter.insert(make_pair(strs[i], s));
    }

    vector<vector<string>> ret;
    for(int i = 0; i < strs.size(); ++i)
    {
        vector<string> v;
        if(ret.empty())
        {
            v.push_back(strs[i]);
            ret.push_back(v);
            continue;
        }

        auto it = filter.find(strs[i]);
        if(it != filter.end())
        {
            bool flag = false;
            for(int j = 0; j < ret.size(); ++j)
            {
                vector<string> temp = ret[j];
                auto t = filter.find(temp[0]);
                if(t != filter.end() && it->second == t->second)
                {
                    flag = true;
                    ret[j].push_back(it->first);
                    break;
                }
            }
            if(!flag)
            {
                v.push_back(strs[i]);
                ret.emplace_back(v);
            }
        }
    }

    return ret;
}

vector<vector<string>> groupAnagrams(vector<string>& strs)
{
    vector<vector<string>> ret;
    unordered_map<string, int> filter;
    int count = 0;
    string s;
    for(auto& str : strs)
    {
        s = str;
        sort(s.begin(), s.end());
        if(filter.count(s))
        {
            ret[filter[s]].emplace_back(str);
        }
        else
        {
            vector<string> v;
            v.emplace_back(str);
            ret.emplace_back(v);
            filter[s] = count++;
        }
    }

    return ret;
}

void print(vector<vector<string>>& v)
{
    for(auto& i : v)
    {
        for(auto& j : i)
            cout << j << " ";
        cout << endl;
    }
}

int main()
{
    vector<string> v{"multiplying","flamboyantly","profession","loft","voluntary","fudges","swore","flanks","diet","pamphlets",
        "dispatchers","afterbirths","boutiques","motifs","massenet","translator","cup","mountbatten",
        "constipated","monotonically","stability","reenact","pols","bowed","berthed","wreathing","ecclesiastes","stylistically",
        "chandigarh","carpenters","freestyle","reflexively","palimpsest","ampul","deliberates","reactor","metals","deforests","coloring","guadalajara",
        "ra","natural","creepies","dankly","disqualifies","hometowns","disengages","papergirls","phrenology","receptors","concessions","judgements",
        "hummocked","whiner","repaying","selvaged","wattest","throats","persecutor","seagram","akimbo","bureaucratically","stepbrothers","transubstantiation",
        "enjoy","couping","rhizome","paramount","raccoon","hafiz","admiration","snakebite","rumors","lasting","ammo","acquirable","harvard","monomaniac",
        "tonnages","rakish","doses","beneficently","essential","statistically","consultancies","cliffs","ringleaders","effusively","condescension",
        "lime","helplessness","jerking","schemers","glosses","grinding","bacterial","stone","disintegrate","enormous","miniaturized","impetuous","nude","fumbles",
        "corpora","beneficiaries","powerlessly","judgment","doctorates","decade","gracelessly","pollard","sangfroid","overspecialized","mews","repaired","islamics",
        "stinks","jasmine","formulate","chloride","septembers","congress","scrap","threshed","mechanizing","egotist","bicepses","grabs","pudding","mariachis","kong",
        "canonicals","bumpiest","mossiest","obsessing","floral","deed","baron","rubbishes","refuting","remainder","woodsier","kapok","instruments","matriculated","cub","marched","librettos","splendor","wyo","silkworm","llewellyn","anesthesia","nagged","wellsprings","stationing","airedale","axed","decors","smug","sucking","humanoid","backside","sacramento","swinburne","sirups","oakum","fumigating","valarie","flotilla","crevices","surmountable","inquiringly","spotters","ferrets","bulldoze","combatant","shane","satiny","camshafts","carped","published","crooners","imperceptible","dispatches","examples","earmuffs","gramme","lung","plied","fallowing","liberties","cratered","mauling","patronizes","flaked","inspects","cusp","wakened","outbalanced","speckled","compose","oleaginous","heiresses","cashiers","ark","premises","narrowness","computations","mongolism","steamy","informant","dice","compounded","acrylic","scrunch","penlight","imputations","clerics","dressmakers","dangers","paying","tunes","murkiest","effusive","misanthropist","alloying","terrorize","costner","virginian","pampering","sufficient","incisors","culotte","gusting","relapsed","headstrong","backspaced","engaged","strikingly","schemed","diversifying","hyper","accountant","nosegay","occluded","underarm","cyclically","amuck","cutlet","perpetrators","malfeasance","pompey","monolingual","cutthroats","hails","delimit","grudging","heraldic","doc","melanges","alerted","disappearance","sharpe","livers","shoemaker","wealthiness","antipersonnel","serbia","guzzled","dmitri","threshes","skyrocketed","ionized","amend","grotesques","containers","platonism","tabbies","lames","infatuation","locus","acquaintance","mouthfuls","coroners","glands","bilges","queasy","dewitt","pidgin","bicentennial","radish","unlawfully","junketed","use","negotiate","hailing","typo","sanity","mallard","incubating","typed","midterm","glacially","maestro","reincarnate","transpiring","strolling","verbena","trapper","flyers","helmsman","mischievous","pendants","rosalie","beatles","carpals","crinkling","recapped","command","rolando","union","bert","hera","mimeographing","vulgarly","pertinacious","markham","borodin","malevolence","resuscitating","interrelationship","indulging","earthling","wishers","bludgeoned","canvassed","canute","microsoft","bikes","hialeah","mountains","physicals","overstepped","cornstalks","temperament","patriots","irreverently","blitz","firewall","sharpshooter","fizzing","handicappers","ultrasonic","halftime","mcnamara","bratislava","clink","anaesthetized","desmond","vaccines","ed","peccaries","mantillas","indemnifications","retypes","scenarios","regressed","sauced","wins","kresge","sparkled","miseries","reformed","moss","tethers","outsizes","contests","funner","wagons","shortness","drivers","estate","coquettish","favorites","watersides","egos","foiling","dismaying","obligating","lit","fiord","s","cautioning","ararat","creditable","caerphilly","tinkers","arrayed","transgressions","temperas","cantaloup","suffragettes","impacts","workplaces","hostlers","feebly","regular","tarring","vetoes","snack","signifying","frisk","diacritic","thea","spirally","floodlit","minibike","concepts","sustain","dissociated","vassaling","credenza","adjacent","blithe","culture","languors","bunker","bucked","pulsar","chromosome","vicky","viewfinders","accosts","nominal","kshatriya","reamer","amorous","signify","nuttiest","tomlin","resume","greatest","learners","brashness","plaiting","feminists","oddness","facelifts","seaport","interdicting","renewed","reprogrammed","smoulder","bernhardt","wangled","choir","listens","crusty","heavenward","failures","per","proctors","edifice","trespassing","displeased","fuddle","partner","motor","editorialize","fishbowls","rangier","chats","wreckage","covet","guzzlers","scapegoats","silicates","szymborska","biplanes","necktie","optic","macao","hyped","medications","nemesis","mandates","splodge","resins","angelica","gaffed","atavistic","petioles","anxiety","killjoys","misuses","nabobs","queens","conceivably","castling","haltingly","serapes","whizz","punctuating","seaweed","eunuchs","bidets","midpoints","breaded","flunky","tithe","urbanized","balcony","winked","goldener","robotics","manichean","garrison","rattles","songbirds","haldane","bankrupting","whitehall","questioningly","gofers","perfection","ghostwriting","mosley","swimmer","soliloquizing","freeholder","draining","outfoxed","flanneling","biggest","licked","trendier","impoverishing","commits","advisement","unclasping","basking","rico","cagiest","auspicious","legislate","trevor","chevrons","proceeds","steward","bloating","resourcefully","anodynes","gallivant","modifier","mugs","verizon","kip","potties","blaine","thud","chastest","hibernate","pastor","rovers","schmaltz","discomfited","prefabricating","cruisers","mutts","sputtered","doable","sheik","laocoon","politicize","wretcheder","rankling","sides","docs","gluing","pickaxed","pedagogical","describe","spec","toni","unimaginative","guidance","distorter","congeniality","harvests","daniel","irrigates","mallomars","sevenths","decisive","stylish","angleworm","dido","conventing","roweling","zing","relish","prearrange","atheistic","goldsmiths","setbacks","topcoat","condoled","compensate","heavenly","voyeurs","judases","shortchanging","trooped","badmouths","requites","immigrating","opticians","swellheads","sated","cannibalizes","continental","frothed","curios","unlike","replications","cormorants","scaramouch","thingamajig","plunged","ainu","bilbao","glops","shoplifting","basses","clark","nerving","bosom","cruciform","throttle","pokey","envelope","medicaid","indifferent","fluency","echelons","espying","twirlers","cathryn","concluding","punctilious","churchgoers","comparing","persimmons","ducal","flatt","wearer","mandarin","iphigenia","rub","playrooms","lorrie","carries","incapacitates","earn","electrified","adrenal","marcher","phrases","antibiotic","eventually","balconies","carton","toggle","molded","protrusions","croquettes","outwears","reciprocals","poisons","homogenized","sufi","tartuffe","retractable","schoolhouses","megaliths","transliteration","surreys","awaited","wetted","participial","subsidized","anticipates","capulet","equate","observable","excrescences","oceanographers","devise","beds","tolling","quilts","hierarchical","cloches","relative","blossoming","woodsheds","at","stilling","spacial","sublet","doggoning","vermilion","rhiannon","yangon","strictest","podding","hittite","stiffened","suited","admonitions","occupational","regulation","fetter","panelists","chillers","irma","aspirant","ayyubid","exceptionable","drunken","tread","carpel","vests","countered","aeroflot","assigned","exhorted","attentions","euclidean","cellars","anons","exhausting","body","clattering","numbered","battled","ventilate","sculptured","imelda","solemner","unimpaired","sequesters","preachier","gums","malignantly","luftwaffe","intact","reinforcement","misses","durante","calculates","susanne","compass","beryls","filibuster","entailing","eclectically","shivers","letting","inflammations","asseverating","psychos","cyrus","hoop","wondrous","ritual","photogenic","josue","magnifier","spitted","theorize","notebooks","pacing","proportions","secretary","cavity","scampering","recline","snyder","sugariest","rowdiest","discommodes","rory","arteries","outranks","inflect","latticework","abusive","gaslights","cactuses","overreaches","mushiest","lagrange","sciatica","bulging","apse","lucked","burying","annoyed","sub","thoroughfares","offshore","villa","vermont","akron","rep","stutterer","stendhal","redeemer","research","lithium","sprucer","unavailing","bulldozer","herringboned","misapply","gybes","frobisher","snippier","career","rhymes","bolivar","esq","alison","backers","motleyest","toots","infelicitous","swaying","telecommunication","reproves","tersely","joyriding","snuffles","crick","jut","preppies","testifies","retooling","grandstands","riveted","dillydally","flute","procreate","peppier","decorating","alcoholics","langland","cohort","eroded","sonnets","consent","jackrabbits","spadework","lunchboxes","anesthesiology","stubbornest","quixotism","ambidextrously","return","stockbroker","aqueduct","fluent","praises","bemoans","missourians","firths","bluenoses","sprained","workbooks","wobblier","bereavement","institutionalizing","shindig","subtitled","knifing","acrylics","cortez","muled","infer","integrates","grid","sentimentalizing","liberia","flamethrower","entity","detoxify","copra","meridians","milieus","atrium","grays","resultants","mincemeat","concentrates","viscountesses","connoting","jerkily","tiger","engendered","spectacular","fritter","billions","puers","wormwood","genuine","sticking","monograph","wander","evacuated","bargained","syphilitics","logging","model","entrapped","tirade","blondie","windmills","incompetent","battlegrounds","leaden","conjectures","testimonials","soil","downcast","polio","remounted","rekindle","disingenuous","paternalistic","adobes","bibliophile","sindbad","gizmo","booing","thoughtlessness","tennis","skillets","woefullest","exult","briggs","womanize","wenches","radiate","hiccups","alexandra","hammer","indicator","hensley","adulteress","tiptoes","urologists","peters","endorse","repulses","squealed","adjudicating","swift","notionally","everything","flown","rediscovered","spinner","lividly","lyra","storeroom","hallelujahs","term","stabbings","wite",
        "corrine","usefully","masters","subhead","gallantry","mercuries","navy","cristina","pray","salamander","asters","purgatory","recidivists","cognac","springsteen","multitude","wilberforce","drizzling","ramification"};
    auto ret = groupAnagrams(v);
    print(ret);
}

