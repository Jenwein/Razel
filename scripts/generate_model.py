# generate_model.py (Updated for API v20250513)

import os
import sys
import json
import time
import argparse
import base64
import requests
import re
from datetime import datetime
from tencentcloud.common import credential
from tencentcloud.common.profile.client_profile import ClientProfile
from tencentcloud.common.profile.http_profile import HttpProfile
from tencentcloud.common.exception.tencent_cloud_sdk_exception import TencentCloudSDKException
# 使用您找到的正确 API 版本 v20250513
from tencentcloud.ai3d.v20250513 import ai3d_client, models

# --- 配置常量 ---
# API 的服务地域，混元3D目前主要在广州地域
TENCENTCLOUD_REGION = "ap-guangzhou"
# 轮询间隔时间（秒）
POLLING_INTERVAL_SECONDS = 20
# 最大等待时间（秒），例如60分钟
MAX_WAIT_TIME_SECONDS = 3600

def sanitize_filename(text):
    """清理文本，使其成为一个合法的文件名"""
    if not text:
        return ""
    text = re.sub(r'[\\/*?:"<>|]', "", text)
    text = text.replace(' ', '_')
    return text[:100]

def main():
    """主函数，用于处理命令行参数和调用API"""
    parser = argparse.ArgumentParser(description="Generate 3D models using Tencent Cloud Hunyuan 3D API (v20250513).")
    
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument('--prompt', type=str, help='Text prompt for Text-to-3D generation.')
    group.add_argument('--image', type=str, help='Path to the input image for Image-to-3D generation.')

    parser.add_argument('--output_path', type=str, default='outputs', help='Directory to save the generated models.')
    
    args = parser.parse_args()

    try:
        # 1. 初始化认证和客户端
        print("Step 1: Initializing Tencent Cloud client...")
        
        secret_id = os.environ.get("TENCENTCLOUD_SECRET_ID")
        secret_key = os.environ.get("TENCENTCLOUD_SECRET_KEY")

        if not secret_id or not secret_key:
            print("Error: TENCENTCLOUD_SECRET_ID and TENCENTCLOUD_SECRET_KEY environment variables not set.")
            sys.exit(1)

        cred = credential.Credential(secret_id, secret_key)
        httpProfile = HttpProfile()
        httpProfile.endpoint = "ai3d.tencentcloudapi.com"

        clientProfile = ClientProfile()
        clientProfile.httpProfile = httpProfile
        client = ai3d_client.Ai3dClient(cred, TENCENTCLOUD_REGION, clientProfile)

        # 2. 提交3D模型生成任务 (使用新的 SubmitHunyuanTo3DRapidJobRequest)
        print("Step 2: Submitting model generation task...")
        req = models.SubmitHunyuanTo3DRapidJobRequest()

        if args.prompt:
            print(f"Mode: Text-to-3D, Prompt: '{args.prompt}'")
            req.Prompt = args.prompt
        else: # args.image
            print(f"Mode: Image-to-3D, Image Path: '{args.image}'")
            if not os.path.exists(args.image):
                print(f"Error: Image file not found at '{args.image}'")
                sys.exit(1)
            
            with open(args.image, "rb") as f:
                image_base64 = base64.b64encode(f.read()).decode('utf-8')
            
            # 新 API 中，图生3D的参数是 InputImageBase64
            req.InputImageBase64 = image_base64

        # 使用新的 client 方法 SubmitHunyuanTo3DRapidJob
        resp = client.SubmitHunyuanTo3DRapidJob(req)
        job_id = resp.JobId
        print(f"Task submitted successfully! Job ID: {job_id}")

        with open("jobs.log", "a") as log_file:
            log_entry = f"[{datetime.now().strftime('%Y-%m-%d %H:%M:%S')}] Submitted Job. ID: {job_id}, Prompt: '{args.prompt}', Image: '{args.image}'\n"
            log_file.write(log_entry)

        # 3. 轮询任务状态 (使用新的 DescribeHunyuanTo3DRapidJobRequest)
        print("\nStep 3: Polling for job status... (This may take several minutes)")
        req_query = models.QueryHunyuanTo3DRapidJobRequest()
        req_query.JobId = job_id
        
        start_time = time.time()
        while True:
            elapsed_time = time.time() - start_time
            if elapsed_time > MAX_WAIT_TIME_SECONDS:
                print(f"\nError: Job timed out after {MAX_WAIT_TIME_SECONDS / 60:.0f} minutes.")
                sys.exit(1)

            # 使用新的 client 方法 QueryHunyuanTo3DRapidJob
            resp_query = client.QueryHunyuanTo3DRapidJob(req_query)
            status = resp_query.Status

            if status == "SUCCEED":
                print("\nJob completed successfully!")
                break
            elif status == "FAILED":
                print(f"\nError: Job failed. Reason: {resp_query.ErrorMessage}. Please check the Tencent Cloud console for details on Job ID: {job_id}")
                sys.exit(1)
            
            time.sleep(POLLING_INTERVAL_SECONDS)

        # 4. 下载模型文件
        print("\nStep 4: Downloading the generated model file(s)...")
        os.makedirs(args.output_path, exist_ok=True)
        
        if not resp_query.ResultFile3Ds:
            print("Error: No model URLs found in the response.")
            sys.exit(1)

        for model_info in resp_query.ResultFile3Ds:
            url = model_info.Url
            file_type = model_info.Type.lower()
            
            base_name = sanitize_filename(args.prompt) if args.prompt else f"image_model_{job_id}"
            filename = f"{base_name}.{file_type}"
            filepath = os.path.join(args.output_path, filename)

            print(f"Downloading {file_type.upper()} model from: {url}")
            
            try:
                response = requests.get(url, stream=True)
                response.raise_for_status()
                with open(filepath, "wb") as f:
                    for chunk in response.iter_content(chunk_size=8192):
                        f.write(chunk)
                print(f"Model saved successfully to: {filepath}")
            except requests.exceptions.RequestException as e:
                print(f"Error downloading file: {e}")
        
        print("\nAll done!")

    except TencentCloudSDKException as err:
        print(f"\nAn API error occurred: {err}")
    except Exception as e:
        print(f"\nAn unexpected error occurred: {e}")

if __name__ == "__main__":
    main()