import sys
import numpy as np
import pandas as pd
from scipy import stats


OUTPUT_TEMPLATE = (
    '"Did more/less users use the search feature?" p-value: {more_users_p:.3g}\n'
    '"Did users search more/less?" p-value: {more_searches_p:.3g}\n'
    '"Did more/less instructors use the search feature?" p-value: {more_instr_p:.3g}\n'
    '"Did instructors search more/less?" p-value: {more_instr_searches_p:.3g}'
)


def main():
    searchdata_file = sys.argv[1]
    file = pd.read_json(searchdata_file, orient='records', lines=True)
    file['used_search'] = file['search_count'] > 0

    old_ui = file[file['uid'] % 2 == 0]
    new_ui = file[file['uid'] % 2 == 1]
    instructor_old = old_ui[old_ui['is_instructor']]
    instructor_new = new_ui[new_ui['is_instructor']]

    old_searched = old_ui[old_ui['used_search']]
    old_not_searched = old_ui[old_ui['used_search'] == False]
    old_inst_searched = old_searched[old_searched['is_instructor']]
    old_inst_not_searched = old_not_searched[old_not_searched['is_instructor']]
    print('----OLD_UI_CATEGORICAL_DATA----')
    print('ALL USERS:', old_searched.count()[0], old_not_searched.count()[0], old_ui.count()[0])
    print('INSTRUCTORS:', old_inst_searched.count()[0], old_inst_not_searched.count()[0], instructor_old.count()[0])

    new_searched = new_ui[new_ui['used_search']]
    new_not_searched = new_ui[new_ui['used_search'] == False]
    new_inst_searched = new_searched[new_searched['is_instructor']]
    new_inst_not_searched = new_not_searched[new_not_searched['is_instructor']]
    print('----NEW_UI_CATEGORICAL_DATA----')
    print('ALL USERS:', new_searched.count()[0], new_not_searched.count()[0], new_ui.count()[0])
    print('INSTRUCTORS:', new_inst_searched.count()[0], new_inst_not_searched.count()[0], instructor_new.count()[0])

    all_contin = [[old_searched.count()[0], old_not_searched.count()[0]], [new_searched.count()[0], new_not_searched.count()[0]]]
    instructor_contin = [[old_inst_searched.count()[0], old_inst_not_searched.count()[0]],
                         [new_inst_searched.count()[0], new_inst_not_searched.count()[0]]]

    print(all_contin)
    print(instructor_contin)

    all_chi2, all_p, all_dof, all_expected = stats.chi2_contingency(all_contin)
    inst_chi2, inst_p, inst_dof, inst_expected = stats.chi2_contingency(instructor_contin)

    all_utest = stats.mannwhitneyu(old_ui['search_count'], new_ui['search_count'], alternative='two-sided')
    inst_utest = stats.mannwhitneyu(instructor_old['search_count'], instructor_new['search_count'], alternative='two-sided')

    # ...

    # Output
    print(OUTPUT_TEMPLATE.format(
        more_users_p=all_p,
        more_searches_p=all_utest.pvalue,
        more_instr_p=inst_p,
        more_instr_searches_p=inst_utest.pvalue,
    ))


if __name__ == '__main__':
    main()