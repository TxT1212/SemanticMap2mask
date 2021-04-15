#!/bin/bash
# for i in Barn Caterpillar Courthouse Family Horse Francis Palace
# do
#     DATASET_PATH=/media/ezxr/data/tanksandtemples/$i
#     # mkdir $DATASET_PATH/semantic
#     # mkdir $DATASET_PATH/semantic/org_binary_mask
#     # mkdir $DATASET_PATH/semantic/images_masked

#     echo $DATASET_PATH/
#     for rgb in $DATASET_PATH/images/*
#     do
#         num_chosen=${rgb%*.jpg}
#         num_chosen=${num_chosen#*images/}
#         # num_chosen=${rgb#*rgb_mask/}

#         mask=$DATASET_PATH/masks/${num_chosen}_mask.png
#         mask_out=$DATASET_PATH/semantic/org_binary_mask/00${num_chosen}.jpg.png
#         out=$DATASET_PATH/semantic/images_masked/00${num_chosen}.png

#         sed -i "8c image_path: \"$rgb\""   $yaml
#         sed -i "9c mask_path: \"$mask\""   $yaml
#         sed -i "10c image_out_path: \"$out\""   $yaml
#         sed -i "11c mask_out_path: \"$mask_out\""   $yaml

#         ~/general_fuctions/build/general_fuctions $yaml


#     done
# done

ws=/media/ezxr/data/Aachen-Day-Night
yaml=/home/ezxr/Downloads/SemanticMap2mask/combine2images.yaml
bin=/home/ezxr/Downloads/SemanticMap2mask/build/general_fuctions
for i in a # Barn Caterpillar Courthouse Family Horse Francis Palace
do
    DATASET_PATH=$ws
    # mkdir $DATASET_PATH/semantic
    # mkdir $DATASET_PATH/semantic/org_binary_mask
    # mkdir $DATASET_PATH/semantic/images_masked
    # mkdir $DATASET_PATH/semantic/erode_binary_mask

    echo $DATASET_PATH/
    # /media/ezxr/data/Aachen-Day-Night/semantic/masks/162_color.png
    for image_choen in $DATASET_PATH/semantic/masks/*_color.png
    do
        num_chosen=${image_choen%*_color.png}
        num_chosen=${num_chosen#*masks/}
        echo $num_chosen
        # /media/ezxr/data/Aachen-Day-Night/images/db/1.jpg
        rgb=$DATASET_PATH/images/db/$num_chosen.jpg
        mask=$DATASET_PATH/semantic/masks/${num_chosen}_mask.png
        mask_out=$DATASET_PATH/semantic/org_binary_mask/${num_chosen}.jpg.png
        mask_erode_out=$DATASET_PATH/semantic/erode_binary_mask/${num_chosen}.jpg.png
        image_out_path=$DATASET_PATH/semantic/images_masked/${num_chosen}.png

        sed -i "8c image_path: \"$rgb\""   $yaml
        sed -i "9c mask_path: \"$mask\""   $yaml
        sed -i "10c image_out_path: \"$image_out_path\""   $yaml
        sed -i "11c mask_out_path: \"$mask_out\""   $yaml
        sed -i "12c mask_erode_out: \"$mask_erode_out\""   $yaml

        $bin $yaml


    done
done