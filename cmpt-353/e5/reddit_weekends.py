import sys
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy import stats


OUTPUT_TEMPLATE = (
    "Initial (invalid) T-test p-value: {initial_ttest_p:.3g}\n"
    "Original data normality p-values: {initial_weekday_normality_p:.3g} {initial_weekend_normality_p:.3g}\n"
    "Original data equal-variance p-value: {initial_levene_p:.3g}\n"
    "Transformed data normality p-values: {transformed_weekday_normality_p:.3g} {transformed_weekend_normality_p:.3g}\n"
    "Transformed data equal-variance p-value: {transformed_levene_p:.3g}\n"
    "Weekly data normality p-values: {weekly_weekday_normality_p:.3g} {weekly_weekend_normality_p:.3g}\n"
    "Weekly data equal-variance p-value: {weekly_levene_p:.3g}\n"
    "Weekly T-test p-value: {weekly_ttest_p:.3g}\n"
    "Mann–Whitney U-test p-value: {utest_p:.3g}"
)

def get_weekday_num(date):
    return date.weekday()

def get_year_week_pair(date):
    return (date.isocalendar()[0], date.isocalendar()[1])

def main():
    reddit_counts = sys.argv[1]

    counts = pd.read_json(reddit_counts, lines=True)
    counts = counts[counts['subreddit'] == 'canada']
    counts = counts[counts['date'].dt.year <= 2013]
    counts = counts[counts['date'].dt.year >= 2012]
    counts['weekday'] = counts['date'].apply(get_weekday_num)

    weekend_counts = counts[counts['weekday'] >= 5]
    weekday_counts = counts[counts['weekday'] < 5]

    init_ttest = stats.ttest_ind(weekday_counts['comment_count'], weekend_counts['comment_count'])
    init_weekend_norm = stats.normaltest(weekend_counts['comment_count'])
    init_weekday_norm = stats.normaltest(weekday_counts['comment_count'])
    init_levene = stats.levene(weekend_counts['comment_count'], weekday_counts['comment_count'])

    transformed_weekend_counts = np.sqrt(weekend_counts['comment_count'])
    transformed_weekday_counts = np.sqrt(weekday_counts['comment_count'])
    transformed_weekend_norm = stats.normaltest(transformed_weekend_counts)
    transformed_weekday_norm = stats.normaltest(transformed_weekday_counts)
    transformed_levene = stats.levene(transformed_weekend_counts, transformed_weekday_counts)

    plt.hist([transformed_weekend_counts, transformed_weekday_counts])
    plt.legend(['Weekend Count', 'Weekday Count'])
    plt.show()

    weekend_counts['year_week'] = weekend_counts['date'].apply(get_year_week_pair)
    weekday_counts['year_week'] = weekday_counts['date'].apply(get_year_week_pair)

    weekly_weekend_counts = weekend_counts.groupby('year_week').mean()['comment_count']
    weekly_weekday_counts = weekday_counts.groupby('year_week').mean()['comment_count']
    # print(weekly_weekday_counts)
    # print(weekly_weekend_counts)

    weekly_weekend_norm = stats.normaltest(weekly_weekend_counts)
    weekly_weekday_norm = stats.normaltest(weekly_weekday_counts)
    weekly_levene = stats.levene(weekly_weekend_counts, weekly_weekday_counts)
    weekly_ttest = stats.ttest_ind(weekly_weekday_counts, weekly_weekend_counts)
    print(weekly_ttest)

    utest = stats.mannwhitneyu(weekday_counts['comment_count'], weekend_counts['comment_count'], alternative='two-sided')
    print(utest)
    # ...

    print(OUTPUT_TEMPLATE.format(
        initial_ttest_p=init_ttest.pvalue,
        initial_weekday_normality_p=init_weekday_norm.pvalue,
        initial_weekend_normality_p=init_weekend_norm.pvalue,
        initial_levene_p=init_levene.pvalue,
        transformed_weekday_normality_p=transformed_weekday_norm.pvalue,
        transformed_weekend_normality_p=transformed_weekend_norm.pvalue,
        transformed_levene_p=transformed_levene.pvalue,
        weekly_weekday_normality_p=weekly_weekday_norm.pvalue,
        weekly_weekend_normality_p=weekly_weekend_norm.pvalue,
        weekly_levene_p=weekly_levene.pvalue,
        weekly_ttest_p=weekly_ttest.pvalue,
        utest_p=utest.pvalue,
    ))


if __name__ == '__main__':
    main()