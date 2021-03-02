#!/bin/bash

source config.sh # tokens

if [ -n "$1" ]
then
    login=$1
else
    login="4m0xa"
fi

data=`curl --silent -X GET "https://api.twitch.tv/helix/users?login=$login" \
-H "client-id: $client_id" -H "Authorization: Bearer $access_token"`

if [ "$data" = "{\"data\":[]}" ]
then
    echo "Login doesn't exists."
    exit 1
fi

user_id=`echo $data | sed -e 's/[{}]/''/g' | \
awk -v k="text" '{n=split($0,a,","); for (i=1; i<=n; i++) print a[i]}' | \
grep "id" | awk -F: '{print $3}' | tr -d \"`

all_ids=""
page=0
live_ids=`mktemp`

# echo $data


echo -n -e "Getting channel follows... \t"
while [[ "$cursor" != "" || "$page" -eq 0 ]]
do

    following_data=`curl --silent -X \
    GET "https://api.twitch.tv/helix/users/follows?from_id=$user_id&&after=$cursor" \
    -H "client-id: $client_id" -H "Authorization: Bearer $access_token"`

    following_ids=`echo $following_data | sed -e 's/[{}]/''/g' | \
    awk -v k="text" '{n=split($0,a,","); for (i=1; i<=n; i++) print a[i]}' | \
    grep "to_id" | awk -F: '{print $2}' | tr -d \"`

    all_ids="$all_ids $following_ids"

    cursor=`echo $following_data | sed -e 's/[{}]/''/g' | \
    awk -v k="text" '{n=split($0,a,","); for (i=1; i<=n; i++) print a[i]}' | \
    grep "cursor" | awk -F\" '{print $(NF-1)}'`

    let "page=page+1"
done

echo "Done"

echo -n -e "Total channels:\t";  echo "$all_ids" | wc -w


# echo $all_ids

# echo $all_logins
# live_ids=""


echo -n -e "Getting live channels... \t"


for id in $all_ids
do
    # echo $login
    (live_id=`curl --silent -X GET "https://api.twitch.tv/helix/streams?user_id=$id" \
    -H "client-id: $client_id" -H "Authorization: Bearer $access_token"`
    if [ "$live_id" != "{\"data\":[],\"pagination\":{}}" ]
    then
        user_name=`echo $live_id | sed -e 's/[{}]/''/g' | \
        awk -v k="text" '{n=split($0,a,","); for (i=1; i<=n; i++) print a[i]}' | \
        grep "user_name" | awk -F: '{print $2}' | tr -d \"`

        game_name=`echo $live_id | sed -e 's/[{}]/''/g' | \
        awk -v k="text" '{n=split($0,a,","); for (i=1; i<=n; i++) print a[i]}' | \
        grep "game_name" | awk -F: '{print $2}' | tr -d \"`

        viewer_count=`echo $live_id | sed -e 's/[{}]/''/g' | \
        awk -v k="text" '{n=split($0,a,","); for (i=1; i<=n; i++) print a[i]}' | \
        grep "viewer_count" | awk -F: '{print $2}' | tr -d \"`

        echo "$user_name streaming $game_name for $viewer_count" >> $live_ids
        # echo $live_ids
    fi) &
done

wait

echo -e "Done\n"
# printf $live_ids
# live_ids=`echo -e $live_ids | awk '{ print $NF, $0 }' | sort -n -k1 -r | sed 's/^[0-9][0-9]* //'`
cat $live_ids | awk '{print $NF,$0}' | sort -n -k1 -r | awk '{$1="";print $0 }'

echo ""
rm $live_ids

exit 0
# echo $live_ids